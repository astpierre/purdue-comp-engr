# define a makefile variable for the java compiler
JCC = javac
# typing 'make' will invoke the first target entry in the makefile 
# (the default one in this case)
default: TalkBehavior.class MoveBehavior.class Bark.class MuteTalk.class Meow.class Walk.class Swim.class Dog.class Fish.class Cat.class Main.class

TalkBehavior.class: TalkBehavior.java
	$(JCC) $(JFLAGS) TalkBehavior.java

MoveBehavior.class: MoveBehavior.java
	$(JCC) $(JFLAGS) MoveBehavior.java

Dog.class: Dog.java
	$(jcc) $(jflags) Dog.java

Cat.class: Cat.java
	$(jcc) $(jflags) Cat.java

Fish.class: Fish.java
	$(jcc) $(jflags) Fish.java

Walk.class: Walk.java
	$(JCC) $(JFLAGS) Walk.java

Swim.class: Swim.java
	$(JCC) $(JFLAGS) Swim.java

Meow.class: Meow.java
	$(JCC) $(JFLAGS) Meow.java

Bark.class: Bark.java
	$(JCC) $(JFLAGS) Bark.java

MuteTalk.class: MuteTalk.java
	$(JCC) $(JFLAGS) MuteTalk.java

Main.class: Main.java
	$(JCC) $(JFLAGS) Main.java

run: Main.class 
	java Main

# To start over from scratch, type 'make clean'.  
# Removes all .class files, so that the next make rebuilds them
clean: 
	rm *.class
