PVector[] pts;
boolean[] clicked;

void setup() {
  size(400, 400);
  
  pts = new PVector[4];
  
  pts[0] = new PVector(50, 50);
  pts[1] = new PVector(200, 50);
  pts[2] = new PVector(350, 200);
  pts[3] = new PVector(350, 350);
  
  clicked = new boolean[4];
  for (int i = 0; i < clicked.length; i++) {
    clicked[i] = false;
  }
}

void draw() {
  background(123);
  
  noFill();
  stroke(200, 0, 0);
  // bezier(8개의 인자, 4개의 점의 각 x, y 좌표)
  
  noStroke();
  fill(0, 200, 200);
  
  int numSeg = 50;
  for (int i = 0; i < numSeg; i++) {
    float amt = i / float(numSeg);
    
    PVector Q0 = PVector.lerp(pts[0], pts[1], amt);
    PVector Q1 = PVector.lerp(pts[1], pts[2], amt);
    PVector Q2 = PVector.lerp(pts[2], pts[3], amt);
    
    PVector R0 = PVector.lerp(Q0, Q1, amt);
    PVector R1 = PVector.lerp(Q1, Q2, amt);
    
    PVector S0 = PVector.lerp(R0, R1, amt);
    
    ellipse(S0.x, S0.y, 6, 6);
  }
  
  noStroke();
  fill(200, 0, 0);
  ellipse(pts[0].x, pts[0].y, 10, 10);
  ellipse(pts[1].x, pts[1].y, 10, 10);
  ellipse(pts[2].x, pts[2].y, 10, 10);
  ellipse(pts[3].x, pts[3].y, 10, 10);
}

void mouseReleased() {
 for (int i = 0; i < pts.length; i++) {
  clicked[i] = false; 
 }
}

void mouseDragged() {
 for (int i = 0; i < pts.length; i++) {
   if (clicked[i] == true) {
    pts[i].x = mouseX;
    pts[i].y = mouseY;
   }
 }
}

void mousePressed() {
  for (int i = 0; i < pts.length; i++) {
     float d = dist(mouseX, mouseY, pts[i].x, pts[i].y);
     if (d < 10) {
        clicked[i] = true;
        break;
     }
  }
}
