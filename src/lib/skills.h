/*
 * skills.h
 */

enum abilities {
  Str, Dex, Con, Int, Wis, Cha
};

enum skills {
  acrobatics, animalHandling, arcana, athletics, deception, history,
  insight, intimidation, investigation, medicine, nature, perception,
  performance, persuasion, religion, slightOfHand, stealth, survival
};

abilities skillAbil[] = {
  Dex, Wis, Int, Str, Cha, Int, 
  Wis, Cha, Int, Wis, Int, Wis,
  Cha, Cha, Int, Dex, Dex, Wis
};
