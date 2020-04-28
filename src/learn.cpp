float*** CreateGrad(float*** Grad,int* mas_info)
{
    int i,j;
    Grad=new float**[mas_info[0]-1];
    for (i=0;i<(mas_info[0]-1);i++)
    {
        Grad[i]=new float*[mas_info[i+1]];
        for (j=0;j<mas_info[i+1];j++)
            Grad[i][j]=new float[mas_info[i+2]];
    }
    return Grad;
}
