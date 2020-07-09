IP_ADDRESS=$1
SSH_PORT=$2

rsync -avz --exclude=src/libbnxrfid/ --exclude=.git/ --exclude=scripts/ -e "ssh -p '${SSH_PORT}'" ../* user@"${IP_ADDRESS}":/home/user/XinoibExamples/. --delete


    