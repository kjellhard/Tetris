pipeline{
    agent any
    stages{
        stage("Compilation"){
            steps{
                bat """
                cd Tetris
                del /f Test.exe
                del /f Tetris.exe
                g++ *.cpp -o Tetris.exe -I"../mingw-include/" -L "../mingw-lib/" -l "sfml-graphics" -l "sfml-window" -l "sfml-system"
                g++ *.cpp -D TESTING -o Test.exe -I"../mingw-include/" -L "../mingw-lib/" -l "sfml-graphics" -l "sfml-window" -l "sfml-system"
                """
                
            }
        }
        stage("Generation"){
            steps{
                catchError(buildResult: 'SUCCESS', stageResult: 'FAILURE')
                    bat """
                    cd Tetris
                    Test.exe Generation
                    """
            }
            
        }
        stage("Rotation"){
            steps {
                bat """
                cd Tetris
                Test.exe Generation
                """
                }
            }
        }
    }
