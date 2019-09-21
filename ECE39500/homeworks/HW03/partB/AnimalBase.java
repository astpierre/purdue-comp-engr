public abstract class AnimalBase {
    MoveBehavior moveBehavior;
    TalkBehavior talkBehavior;

    public AnimalBase() {
    }

    public void setMoveBehavior(MoveBehavior mb) {
        moveBehavior = mb;
    }

    public void setTalkBehavior(TalkBehavior tb) {
        talkBehavior = tb;
    }

    abstract void display();

    public void performMove() {
        moveBehavior.move();
    }

    public void performTalk() {
        talkBehavior.talk();
    }

}