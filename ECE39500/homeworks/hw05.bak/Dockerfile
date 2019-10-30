FROM openjdk:8
COPY . /usr/src/myapp
WORKDIR /usr/src/myapp
RUN javac MatrixMultiply.java
RUN javac MatrixCommander.java
RUN javac Main.java
CMD ["java", "Main"]
