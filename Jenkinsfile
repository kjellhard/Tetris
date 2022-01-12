pipeline{
    agent any
    stages{
        stage("hello"){
            steps{
                bat """
                cd Tetris
                del /f Tetris.exe
                main.cpp Tetris.cpp DispText.cpp Globals.cpp -o Tetris.exe -I"../mingw-include/" -L "../mingw-lib/" -l "sfml-graphics" -l "sfml-window" -l "sfml-system"
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
