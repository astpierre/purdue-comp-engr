public class Main {

    public static void main(String[] args) {
        /*
        Part B. Create an Animal class that simulates many kinds of animals, not just ducks.

        It should support a MoveBehavior, and a TalkBehavior.
            Implement a Dog, Cat and Fish.
                The Dog uses a Walk MoveBehavior and a Bark TalkBehavior.
                The Cat uses a Walk MoveBehavior and a Meow TalkBehavior.
                The Fish uses a Swim MoveBehavior and a Mute TalkBehavior.
         */

        MoveBehavior move_cat = new Walk();
        MoveBehavior move_dog = new Walk();
        MoveBehavior move_fish = new Swim();

        TalkBehavior talk_cat = new Meow();
        TalkBehavior talk_dog = new Bark();
        TalkBehavior talk_fish = new MuteTalk();

        Dog dog = new Dog(move_dog, talk_dog);
        Cat cat = new Cat(move_cat, talk_cat);
        Fish fish = new Fish(move_fish, talk_fish);

        dog.display();
        dog.move();
        dog.talk();

        cat.display();
        cat.move();
        cat.talk();

        fish.display();
        fish.move();
        fish.talk();
    }
}