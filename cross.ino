void cross(const float m[],const float n[], float p[]) // pass p[] and change it in the cross function because you can't return array in C. Funciton can change input arrays because they're pointers. Doing const float m[] means the function is not allowed to change m[].
{
  p[0]=n[1]*m[2]-m[1]*n[2];
  p[1]=m[0]*n[2]-n[0]*m[2];
  p[2]=n[0]*m[1]-m[0]*n[1];
  
}//end cross function
