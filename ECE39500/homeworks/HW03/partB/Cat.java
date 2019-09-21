public class Cat {
    MoveBehavior moveBehavior;
    TalkBehavior talkBehavior;

    public Cat() {
        moveBehavior = new Walk();
        talkBehavior = new Meow();
    }

    public Cat(MoveBehavior mb, TalkBehavior wb) {
        this.moveBehavior = mb;
        this.talkBehavior = wb;
    }

    public void display() {
        System.out.println("I'm a mean cat!");
    }
}
