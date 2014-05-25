def safe_task(&block)
  yield
rescue Exception => problem
    puts "rake task interupted: #{problem}"
end

desc 'Cleans the project by deleting everything listed in .gitignore'
task :clean do
    file = File.new(".gitignore", "r")
    while (line = file.gets)
        sh "rm -rf #{line}"
    end
    file.close
end

desc 'Generates makefiles using CMake'
task :configure do
    sh 'mkdir -p build && cd build && cmake ..'
end

desc 'Builds the application and unit tests using Make'
task :compile do
    sh "make -C build"
end

desc 'Executes the unit tests'
task :test do
    safe_task do
        sh "make -C build test"
    end
    sh "cat build/Testing/Temporary/LastTest.log"
end

desc 'Starts the application'
task :start do
    sh "bin/moomin"
end

desc 'Alias for rake configure compile test'
task :default do
    Rake::Task["configure"].invoke
    Rake::Task["compile"].invoke
    Rake::Task["test"].invoke
end

desc 'Alias for rake clean default'
task :all do
    Rake::Task["clean"].invoke
    Rake::Task["default"].invoke
end
