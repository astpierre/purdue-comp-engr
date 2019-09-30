1. install java development kit
sudo apt-get install default-jdk

2. copy path to jdk
update-alternatives --config java

3. add path to /etc/environment
JAVA_HOME="/usr/local/java/jdk-11.0.2/bin/java"

source /etc/environment

echo $JAVA_HOME
curl -s "https://get.sdkman.io" | bash
source "$HOME/.sdkman/bin/sdkman-init.sh"

sdk install gradle 5.2.1

gradle init --type java-application
