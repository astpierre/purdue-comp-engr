public class Dog {
    MoveBehavior moveBehavior;
    TalkBehavior talkBehavior;

    public Dog() {
        moveBehavior = new Walk();
        talkBehavior = new Bark();
    }

    public Dog(MoveBehavior mb, TalkBehavior bb) {
        this.moveBehavior = mb;
        this.talkBehavior = bb;
    }

    public void display() {
        System.out.println("I'm a cute puppy!");
    }
}