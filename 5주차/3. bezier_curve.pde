PVector p1;
PVector c1;
PVector c2;
PVector p2;

void setup() {
  size(400, 400);
  
  p1 = new PVector(50, 50);
  c1 = new PVector(200, 50);
  c2 = new PVector(350, 200);
  p2 = new PVector(350, 350);
}

void draw() {
  background(123);
  
  noFill();
  stroke(200, 0, 0);
  noStroke();
  fill(0, 200, 200);
  
  int numSeg = 50;
  for (int i = 0; i < numSeg; i++) {
    float amt = i / float(numSeg);
    
    PVector Q0 = PVector.lerp(p1, c1, amt);
    PVector Q1 = PVector.lerp(c1, c2, amt);
    PVector Q2 = PVector.lerp(c2, p2, amt);
    
    PVector R0 = PVector.lerp(Q0, Q1, amt);
    PVector R1 = PVector.lerp(Q1, Q2, amt);
    
    PVector S0 = PVector.lerp(R0, R1, amt);
    
    ellipse(S0.x, S0.y, 6, 6);
  }
  
  noStroke();
  fill(200, 0, 0);
  ellipse(p1.x, p1.y, 10, 10);
  ellipse(c1.x, c1.y, 10, 10);
  ellipse(c2.x, c2.y, 10, 10);
  ellipse(p2.x, p2.y, 10, 10);
}
