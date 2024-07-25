export OBELISK_EXAMPLES_ROOT="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
env_file="$OBELISK_EXAMPLES_ROOT/docker/.env"
if [ -f $env_file ]; then
    rm $env_file
fi
touch $env_file
echo "USER=$USER" > $env_file
echo "UID=$(id -u)" >> $env_file
echo "GID=$(id -g)" >> $env_file
echo "OBELISK_EXAMPLES_ROOT=$OBELISK_EXAMPLES_ROOT" >> $env_file
echo -e "\033[1;32m.env file populated under $OBELISK_EXAMPLES_ROOT/docker!\033[0m"
