[%%debugger.chrome];

type state =
  | FaceUp
  | FaceDown;

type group =
  | A
  | B;

type t = {
  animal: Animal.t,
  group,
  state,
};

let initialize = (animal, group) => {animal, group, state: FaceDown};

let makePair = animal => [initialize(animal, A), initialize(animal, B)];

let key = ({group, animal}) => {
  let groupString =
    switch (group) {
    | A => "1"
    | B => "2"
    };
  Animal.toString(animal) ++ groupString;
};

let imageUrl = ({state, animal}) =>
  switch (state) {
  | FaceUp => Animal.url(animal)
  | FaceDown => "blue.svg"
  };

let isMatch = ({animal: a}, {animal: b}) => a == b;

let isSameCard = ({group: a} as c1, {group: b} as c2) =>
  isMatch(c1, c2) && a == b;

let flip = card => {...card, state: FaceUp};
let reset = card => {...card, state: FaceDown};