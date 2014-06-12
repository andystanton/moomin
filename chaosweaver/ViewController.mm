//
//  ViewController.m
//  chaosweaver
//
//  Created by Andy Stanton on 08/06/2014.
//
//

#import "ViewController.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

// Uniform index.
enum
{
    UNIFORM_MODELVIEWPROJECTION_MATRIX,
    UNIFORM_NORMAL_MATRIX,
    NUM_UNIFORMS
};
GLint uniforms[NUM_UNIFORMS];

// Attribute index.
enum
{
    ATTRIB_VERTEX,
    ATTRIB_NORMAL,
    NUM_ATTRIBUTES
};

@interface ViewController () {
}
@property (strong, nonatomic) EAGLContext *context;
@property (strong, nonatomic) GLKBaseEffect *effect;

@property (readwrite) PhysicsHelper * physicsHelper;
@property WorldRenderer * worldRenderer;

@property Vec2 * viewLowerLeft;
@property Vec2 * viewUpperRight;

@property Vec2 * nextViewLowerLeft;
@property Vec2 * nextViewUpperRight;

@property BOOL isCircles;
@property BOOL launching;
@property BOOL panning;

@property float worldWidth;
@property float worldHeight;

@property float currentScale;

@property double lastUpdate;

@property CGPoint startTouchPositionA;
@property CGPoint startTouchPositionB;

@property CGPoint endTouchPositionA;
@property CGPoint endTouchPositionB;

- (void)setupGL;
- (void)tearDownGL;

- (int)loadChaosShaders;
- (BOOL)compileShader:(GLuint *)shader type:(GLenum)type file:(NSString *)file;
- (BOOL)linkProgram:(GLuint)prog;
- (BOOL)validateProgram:(GLuint)prog;
@end

@implementation ViewController


- (BOOL)canBecomeFirstResponder {
    return YES;
}

- (void)viewDidAppear:(BOOL)animated {
    [self becomeFirstResponder];
}

- (void)motionEnded:(UIEventSubtype)motion withEvent:(UIEvent *)event {
    if (motion == UIEventSubtypeMotionShake)
    {
        self.isCircles = !self.isCircles;
        if(self.isCircles)
        {
            self.physicsHelper->addCirclesLatticeCentre();
        } else
        {
            self.physicsHelper->addAABBsLatticeCentre();
        }
    }
}

- (void)clipVec2Pair:(Vec2 *)lowerLeft :(Vec2 *)upperRight
{
    if (upperRight->getY() > self.worldHeight) {
        lowerLeft->setY(lowerLeft->getY() - (upperRight->getY() - self.worldHeight));
        upperRight->setY(self.worldHeight);
    }
    if (upperRight->getX() > self.worldWidth) {
        lowerLeft->setX(lowerLeft->getX() - (upperRight->getX() - self.worldWidth));
        upperRight->setX(self.worldWidth);
    }
    if (lowerLeft->getY() < 0) {
        upperRight->setY(upperRight->getY() - lowerLeft->getY());
        lowerLeft->setY(0);
    }
    if (lowerLeft->getX() < 0) {
        upperRight->setX(upperRight->getX() - lowerLeft->getX());
        lowerLeft->setX(0);
    }
    
    lowerLeft->setX(lowerLeft->getX() < 0 ? 0 : lowerLeft->getX());
    lowerLeft->setY(lowerLeft->getY() < 0 ? 0 : lowerLeft->getY());
    upperRight->setX(upperRight->getX() > self.worldWidth ? self.worldWidth : upperRight->getX());
    upperRight->setY(upperRight->getY() > self.worldHeight ? self.worldHeight : upperRight->getY());
}

- (void)handlePinch:(UIPinchGestureRecognizer *)gestureRecognizer
{
    Vec2 currentDiff = (*self.viewUpperRight - *self.viewLowerLeft);
    
    // scale the current fixed view but make sure it can't be larger than the world
    
    double scale = gestureRecognizer.scale;
    scale = scale < 0.1 ? 0.1 : scale;
    
    Vec2 resizedDiff = currentDiff / scale;
    if (resizedDiff.getX() > self.worldWidth || resizedDiff.getY() > self.worldHeight) {
        resizedDiff.setX(self.worldWidth);
        resizedDiff.setY(self.worldHeight);
    }

    // we assume zoom on centre, so we need half of the difference between the
    // original view and the new one. we add to the lower left and subtract from
    // the upper right
    
    Vec2 offset = (currentDiff - resizedDiff) / 2;

    if([gestureRecognizer state] == UIGestureRecognizerStateChanged) {
        
        // update the current view with the scale offset
        
        
        // normalise
        *self.nextViewLowerLeft = *self.viewLowerLeft + offset;
        *self.nextViewUpperRight = *self.viewUpperRight - offset;
        

        [self clipVec2Pair:self.nextViewLowerLeft :self.nextViewUpperRight];

        
        self.worldRenderer->lookAt(*self.nextViewLowerLeft, *self.nextViewUpperRight);
        
    } else if([gestureRecognizer state] == UIGestureRecognizerStateEnded) {
        
        // when the gesture finishes, finalise the current view coordinates
        
        *self.viewLowerLeft += offset;
        *self.viewUpperRight -= offset;
        
        // finalise the scale factor but make sure it can never be greater than 1
        
        self.currentScale /= scale;
        self.currentScale = self.currentScale > 1 ? 1 : self.currentScale;

        
        // normalise
        [self clipVec2Pair:self.viewLowerLeft :self.viewUpperRight];
        
        // and update the current view
        self.worldRenderer->lookAt(*self.viewLowerLeft, *self.viewUpperRight);
    }
}

- (void)handlePan:(UIPanGestureRecognizer *)gestureRecognizer
{
   
    if ([gestureRecognizer numberOfTouches] >= 2) {
        if ([gestureRecognizer state] == UIGestureRecognizerStateBegan) {
            self.startTouchPositionA = [gestureRecognizer locationOfTouch:0 inView:gestureRecognizer.view];
            self.startTouchPositionB = [gestureRecognizer locationOfTouch:1 inView:gestureRecognizer.view];
            self.panning = true;
        } else if([gestureRecognizer state] == UIGestureRecognizerStateChanged) {
            self.endTouchPositionA = [gestureRecognizer locationOfTouch:0 inView:gestureRecognizer.view];
            self.endTouchPositionB = [gestureRecognizer locationOfTouch:1 inView:gestureRecognizer.view];
            
            Vec2 endMidpoint = (Vec2(self.endTouchPositionB.x, self.endTouchPositionB.y) + Vec2(self.endTouchPositionA.x, self.endTouchPositionA.y))/2;
            Vec2 startMidpoint = (Vec2(self.startTouchPositionB.x, self.startTouchPositionB.y) + Vec2(self.startTouchPositionA.x, self.startTouchPositionA.y))/2;
            
            Vec2 offset = endMidpoint - startMidpoint;
            offset.setY(-offset.getY());
            offset *= 10;
            
            NSLog(@"we've moved by %s", offset.toString().c_str());

            *self.nextViewLowerLeft = *self.viewLowerLeft - offset;
            *self.nextViewUpperRight = *self.viewUpperRight - offset;
            
            [self clipVec2Pair:self.nextViewLowerLeft :self.nextViewUpperRight];
            
            //self.worldRenderer->lookAt(*self.nextViewLowerLeft, *self.nextViewUpperRight);
        }
    } else {
        if (self.panning) {
            NSLog(@"stopped panning");
            //self.viewLowerLeft = self.nextViewLowerLeft;
            //self.viewUpperRight = self.nextViewUpperRight;
            self.panning = false;
        }
        
        if([gestureRecognizer numberOfTouches] == 1) {
            if ([gestureRecognizer state] == UIGestureRecognizerStateBegan) {
                self.startTouchPositionA = [gestureRecognizer locationOfTouch:0 inView:gestureRecognizer.view];
                self.launching = true;
            }
        } else if([gestureRecognizer numberOfTouches] == 0)
        {
            if([gestureRecognizer state] == UIGestureRecognizerStateEnded) {
                if (self.launching) {
                    CGPoint currentPos = [gestureRecognizer translationInView:([gestureRecognizer view])];
                    
                    double posX = self.viewLowerLeft->getX() + self.startTouchPositionA.x * 10 * self.currentScale;
                    double posY = self.viewUpperRight->getY() - self.startTouchPositionA.y * 10 * self.currentScale;
                    
                    double endX = posX + currentPos.x * 10 * self.currentScale;
                    double endY = posY - currentPos.y * 10 * self.currentScale;
                    
                    self.physicsHelper->spawnEntityOnTrajectory(Vec2(posX, posY), Vec2(endX, endY));
                    
                    self.startTouchPositionA = CGPointZero;
                    self.startTouchPositionB = CGPointZero;
                    self.endTouchPositionA = CGPointZero;
                    self.endTouchPositionB = CGPointZero;
                }
            }
        }

    }
}


- (void)viewDidLoad
{
    [super viewDidLoad];

    self.isCircles = true;
    self.currentScale = 1.0;
    
    
    UIPinchGestureRecognizer *pinchGesture = [[UIPinchGestureRecognizer alloc] initWithTarget:self action:@selector(handlePinch:)];
    [self.view addGestureRecognizer:pinchGesture];

    UIPanGestureRecognizer *panGesture = [[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(handlePan:)];
    [self.view addGestureRecognizer:panGesture];
    
    
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];

    if (!self.context) {
        NSLog(@"Failed to create ES context");
    }
    
    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    
    
    
    [self setupGL];
}

- (void)dealloc
{    
    [self tearDownGL];
    
    if ([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext:nil];
    }
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];

    if ([self isViewLoaded] && ([[self view] window] == nil)) {
        self.view = nil;
        
        [self tearDownGL];
        
        if ([EAGLContext currentContext] == self.context) {
            [EAGLContext setCurrentContext:nil];
        }
        self.context = nil;
    }

    // Dispose of any resources that can be recreated.
}

- (void)setupGL
{
    [EAGLContext setCurrentContext:self.context];
    
    NSLog(@"%f, %f", self.view.bounds.size.width, self.view.bounds.size.height);
    
    self.worldWidth = self.view.bounds.size.width * 10;
    self.worldHeight = self.view.bounds.size.height * 10;
    
    self.lastUpdate = [[NSDate date] timeIntervalSince1970];
    
    self.physicsHelper = new PhysicsHelper(self.worldWidth, self.worldHeight);
    //    self.physicsHelper->addChaosLattice(false);
        self.physicsHelper->addCirclesLatticeCentre();
    //    self.physicsHelper->addAABBsLatticeCentre();

    self.worldRenderer = new WorldRenderer(self.physicsHelper->getEntities(), self.worldWidth, self.worldHeight, [self loadChaosShaders]);
    
    self.viewLowerLeft = new Vec2(Vec2::ORIGIN);
    self.viewUpperRight = new Vec2(self.worldWidth, self.worldHeight);
    
    self.nextViewLowerLeft = new Vec2(*self.viewLowerLeft);
    self.nextViewUpperRight = new Vec2(*self.viewUpperRight);
    
    self.worldRenderer->setZoom(self.viewLowerLeft, self.viewUpperRight);
}

- (void)tearDownGL
{
    [EAGLContext setCurrentContext:self.context];
    
    delete self.worldRenderer;
    delete self.physicsHelper;
    
    self.effect = nil;
}

#pragma mark - GLKView and GLKViewController delegate methods

- (void)update
{
    double time = [[NSDate date] timeIntervalSince1970];
    self.physicsHelper->step((time - self.lastUpdate));
    self.lastUpdate = time;
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    //    [self.effect prepareToDraw];
    
    glClearColor(0.2, 0.2, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    self.worldRenderer->draw();
}

- (int)loadChaosShaders
{
    GLuint vertShader, fragShader;
    NSString *vertShaderPathname, *fragShaderPathname;

    
    // Create shader program.
    int chaosProgram = glCreateProgram();
    
    // Create and compile vertex shader.
    vertShaderPathname = [[NSBundle mainBundle] pathForResource:@"EntityVertexShader" ofType:@"vertexshader"];
    if (![self compileShader:&vertShader type:GL_VERTEX_SHADER file:vertShaderPathname]) {
        NSLog(@"Failed to compile vertex shader");
        return NO;
    }
    
    // Create and compile fragment shader.
    fragShaderPathname = [[NSBundle mainBundle] pathForResource:@"EntityFragmentShader" ofType:@"fragmentshader"];
    if (![self compileShader:&fragShader type:GL_FRAGMENT_SHADER file:fragShaderPathname]) {
        NSLog(@"Failed to compile fragment shader");
        return NO;
    }
    
    // Attach vertex shader to program.
    glAttachShader(chaosProgram, vertShader);
    
    // Attach fragment shader to program.
    glAttachShader(chaosProgram, fragShader);
    
    // Link program.
    if (![self linkProgram:chaosProgram]) {
        NSLog(@"Failed to link program: %d", chaosProgram);
        
        if (vertShader) {
            glDeleteShader(vertShader);
            vertShader = 0;
        }
        if (fragShader) {
            glDeleteShader(fragShader);
            fragShader = 0;
        }
        if (chaosProgram) {
            glDeleteProgram(chaosProgram);
            chaosProgram = 0;
        }
        
        return NO;
    }
    
    // Release vertex and fragment shaders.
    if (vertShader) {
        glDetachShader(chaosProgram, vertShader);
        glDeleteShader(vertShader);
    }
    if (fragShader) {
        glDetachShader(chaosProgram, fragShader);
        glDeleteShader(fragShader);
    }
    
    return chaosProgram;
}


- (BOOL)compileShader:(GLuint *)shader type:(GLenum)type file:(NSString *)file
{
    GLint status;
    const GLchar *source;
    
    source = (GLchar *)[[NSString stringWithContentsOfFile:file encoding:NSUTF8StringEncoding error:nil] UTF8String];
    if (!source) {
        NSLog(@"Failed to load vertex shader");
        return NO;
    }
    
    *shader = glCreateShader(type);
    glShaderSource(*shader, 1, &source, NULL);
    glCompileShader(*shader);
    
#if defined(DEBUG)
    GLint logLength;
    glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetShaderInfoLog(*shader, logLength, &logLength, log);
        NSLog(@"Shader compile log:\n%s", log);
        free(log);
    }
#endif
    
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);
    if (status == 0) {
        glDeleteShader(*shader);
        return NO;
    }
    
    return YES;
}

- (BOOL)linkProgram:(GLuint)prog
{
    GLint status;
    glLinkProgram(prog);
    
#if defined(DEBUG)
    GLint logLength;
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetProgramInfoLog(prog, logLength, &logLength, log);
        NSLog(@"Program link log:\n%s", log);
        free(log);
    }
#endif
    
    glGetProgramiv(prog, GL_LINK_STATUS, &status);
    if (status == 0) {
        return NO;
    }
    
    return YES;
}

- (BOOL)validateProgram:(GLuint)prog
{
    GLint logLength, status;
    
    glValidateProgram(prog);
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetProgramInfoLog(prog, logLength, &logLength, log);
        NSLog(@"Program validate log:\n%s", log);
        free(log);
    }
    
    glGetProgramiv(prog, GL_VALIDATE_STATUS, &status);
    if (status == 0) {
        return NO;
    }
    
    return YES;
}

@end
