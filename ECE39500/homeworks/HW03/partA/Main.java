public class Main {

    public static void main(String[] args) {

        FlyBehavior propel = new FlyWithPropellers();
        QuackBehavior noQuack = new NoQuack();

        RadioControlDuck radioDuckie = new RadioControlDuck(propel, noQuack);

        radioDuckie.performFly();
        radioDuckie.performQuack();
    }
}