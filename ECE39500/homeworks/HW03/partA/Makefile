# define a makefile variable for the java compiler
JCC = javac
# typing 'make' will invoke the first target entry in the makefile 
# (the default one in this case)
default: QuackBehavior.class FlyBehavior.class Quack.class NoQuack.class FlyWithPropellers.class Duck.class RadioControlDuck.class Main.class

QuackBehavior.class: QuackBehavior.java
	$(JCC) $(JFLAGS) QuackBehavior.java

FlyBehavior.class: FlyBehavior.java
	$(JCC) $(JFLAGS) FlyBehavior.java

Duck.class: Duck.java
	$(JCC) $(JFLAGS) Duck.java

RadioControlDuck.class: RadioControlDuck.java
	$(JCC) $(JFLAGS) RadioControlDuck.java

Quack.class: Quack.java
	$(JCC) $(JFLAGS) Quack.java

NoQuack.class: NoQuack.java
	$(JCC) $(JFLAGS) NoQuack.java

FlyWithPropellers.class: FlyWithPropellers.java
	$(JCC) $(JFLAGS) FlyWithPropellers.java

Main.class: Main.java
	$(JCC) $(JFLAGS) Main.java

run: Main.class 
	java Main

# To start over from scratch, type 'make clean'.  
# Removes all .class files, so that the next make rebuilds them
clean: 
	rm *.class
