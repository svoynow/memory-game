[%%debugger.chrome];

type t =
  | Badger
  | Bee
  | Bird
  | Butterfly
  | Cat
  | Chicken
  | Cow
  | Crab
  | Deer
  | Dinosaur
  | Dog
  | Dolphin
  | Elephant
  | Duck
  | Frog
  | Gorilla
  | Horse
  | Kangaroo
  | Leopard
  | Lion
  | Llama
  | Octopus
  | Rhinoceros
  | Shark
  | Sheep
  | Snail
  | Turtle
  | Whale
  | Wolf;

let all = [
  Badger,
  Bee,
  Bird,
  Butterfly,
  Cat,
  Chicken,
  Cow,
  Crab,
  Deer,
  Dinosaur,
  Dog,
  Dolphin,
  Elephant,
  Duck,
  Frog,
  Gorilla,
  Horse,
  Kangaroo,
  Leopard,
  Lion,
  Llama,
  Octopus,
  Rhinoceros,
  Shark,
  Sheep,
  Snail,
  Turtle,
  Whale,
  Wolf,
];

let toString = (animal: t) =>
  switch (animal) {
  | Badger => "Badger"
  | Bee => "Bee"
  | Bird => "Bird"
  | Butterfly => "Butterfly"
  | Cat => "Cat"
  | Chicken => "Chicken"
  | Cow => "Cow"
  | Crab => "Crab"
  | Deer => "Deer"
  | Dinosaur => "Dinosaur"
  | Dog => "Dog"
  | Dolphin => "Dolphin"
  | Elephant => "Elephant"
  | Duck => "Duck"
  | Frog => "Frog"
  | Gorilla => "Gorilla"
  | Horse => "Horse"
  | Kangaroo => "Kangaroo"
  | Leopard => "Leopard"
  | Lion => "Lion"
  | Llama => "Llama"
  | Octopus => "Octopus"
  | Rhinoceros => "Rhinoceros"
  | Shark => "Shark"
  | Sheep => "Sheep"
  | Snail => "Snail"
  | Turtle => "Turtle"
  | Whale => "Whale"
  | Wolf => "Wolf"
  };

let url = (animal: t) => toString(animal) ++ ".svg";