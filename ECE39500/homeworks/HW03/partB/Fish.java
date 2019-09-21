public class Fish {
    MoveBehavior moveBehavior;
    TalkBehavior talkBehavior;

    public Fish() {
        moveBehavior = new Swim();
        talkBehavior = new MuteTalk();
    }

    public Fish(MoveBehavior sb, TalkBehavior mb) {
        this.moveBehavior = sb;
        this.talkBehavior = mb;
    }

    public void display() {
        System.out.println("I'm a magestic fish!");
    }
}
