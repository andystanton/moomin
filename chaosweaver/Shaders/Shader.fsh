//
//  Shader.fsh
//  chaosweaver
//
//  Created by Andy Stanton on 08/06/2014.
//
//

varying lowp vec4 colorVarying;

void main()
{
    gl_FragColor = colorVarying;
}
