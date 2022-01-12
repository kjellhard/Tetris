pipeline{
    agent any
    stages{
        stage("hello"){
            steps{
                bat """
                dir
                """
                
            }
        }
        stage("second"){
            steps{
                echo "hej" 
            }
            
        }
        stage("third"){
            steps {
                      echo "This > app.sh"
                }
            }
        }
    }
