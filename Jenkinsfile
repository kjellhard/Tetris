pipeline{
    agent any
    stages{
        stage("hello"){
            steps{
                bat """
                cd HelloWorld
                del /f HelloWorld.exe
                g++ main.cpp -o HelloWorld.exe
                """
                
            }
        }
        stage("second"){
            steps{
                bat """
                cd HelloWorld
                HelloWorld.exe
                """
            }
            
        }
        stage("third"){
            steps {
                      echo "This > app.sh"
                }
            }
        }
    }
