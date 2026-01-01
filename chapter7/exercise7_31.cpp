//Define class X (has Y*) and class Y (has X*) => we need <forward-declaration>
class Y; 

class X {
  Y* y;
};

class Y {
  X* x;
};