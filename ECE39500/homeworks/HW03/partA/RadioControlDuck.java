public class RadioControlDuck extends Duck {

    public RadioControlDuck() {
        flyBehavior = new FlyWithPropellers();
        quackBehavior = new NoQuack();
    }

    public RadioControlDuck(FlyBehavior flyBehavior, QuackBehavior quackBehavior) {
        this.flyBehavior = flyBehavior;
        this.quackBehavior = quackBehavior;
    }

    public void display() {
        System.out.println("I'm a radio controlled duckie");
    }
}