def safe_task(&block)
  yield
rescue Exception => problem
    puts "rake task interupted: #{problem}"
end

task :clean do
    file = File.new(".gitignore", "r")
    while (line = file.gets)
        sh "rm -rf #{line}"
    end
    file.close
end

task :configure do
    sh 'mkdir -p build && cd build && cmake ..'
end

task :compile do
    sh "make -C build"
end

task :test do
    safe_task do
        sh "make -C build test"
    end
    sh "cat build/Testing/Temporary/LastTest.log"
end

task :start do
    sh "bin/moomin"
end

task :default do
    Rake::Task["configure"].invoke
    Rake::Task["compile"].invoke
    Rake::Task["test"].invoke
end

task :all do
    Rake::Task["clean"].invoke
    Rake::Task["default"].invoke
end
