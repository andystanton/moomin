require 'fileutils'

def safe_task(&block)
    yield
rescue Exception => problem
    puts "rake task interupted: #{problem}"
end

desc 'Cleans the project by deleting everything listed in .gitignore'
task :clean do
    puts 'Executing clean...'

    count = 0
    file = File.new(".gitignore", "r")
    while (line = file.gets)
        count += 1
        sh "rm -rf #{line}"
    end
    file.close

    puts "Cleaned #{count} files"
end

desc 'Generates makefiles using CMake'
task :configure do
    puts 'Executing configure...'

    mkdir_p('build')
    Dir.chdir('build') do
        sh "cmake .."
    end
end

desc 'Builds the application and unit tests using Make'
task :compile do
    puts 'Executing compile...'

    sh "make -C build"
end

desc 'Executes the unit tests'
task :test do
    puts 'Executing test...'

    safe_task do
        sh "make -C build test"
    end

    sh "cat build/Testing/Temporary/LastTest.log"
end

desc 'Starts the application'
task :start do
    puts 'Executing start...'

    sh "bin/moomin"
end

desc 'Alias for rake configure compile test'
task :default do
    puts 'Executing default...'

    Rake::Task["configure"].invoke
    Rake::Task["compile"].invoke
    Rake::Task["test"].invoke
end

desc 'Alias for rake clean default'
task :all do
    puts 'Executing all...'

    Rake::Task["clean"].invoke
    Rake::Task["default"].invoke
end
