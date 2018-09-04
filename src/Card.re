type group =
  | A
  | B;

type t = {
  animal: Animal.t,
  group,
};

let initialize = (animal, group) => {animal, group};

let makePair = animal => [initialize(animal, A), initialize(animal, B)];

let key = ({group, animal}) => {
  let groupString =
    switch (group) {
    | A => "1"
    | B => "2"
    };
  Animal.toString(animal) ++ groupString;
};

let imageUrl = ({animal}) => Animal.url(animal);

let isMatch = ({animal: a}, {animal: b}) => a == b;

let isSameCard = ({group: a} as c1, {group: b} as c2) =>
  isMatch(c1, c2) && a == b;