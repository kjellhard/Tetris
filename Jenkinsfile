pipeline{
    agent any
    stages{
        stage("hello"){
            steps{
                bat """
                cd Tetris
                del /f Tetris.exe
                g++ main.cpp -o Tetris.exe
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
