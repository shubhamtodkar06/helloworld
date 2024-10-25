import java.util.*;

public class spiral{
//code to print a given matrix in spiral form.
public static void spiral_method(int[][] martix, int size, int size1)
{
  int top = 0;
  int bottom = size - 1;
  int left = 0;
  int right = size1 - 1;

  while (top <= bottom && left <= right)
  {
    for (int i = left; i <= right; i++)
    {
      System.out.print(martix[top][i] + " ");
    }
    for (int i = top + 1; i <= bottom; i++)
    {
      System.out.print(martix[i][right] + " ");
    }

    for (int i = right - 1; i <= left; i--)
    {
      System.out.print(martix[bottom][i] + " ");
    }

    for (int i = bottom - 1 ; i <= top + 1; i--)
    {
      System.out.print(martix[i][left] + " ");
    }


    top +=1;
    bottom -= 1;
    right -= 1;
    left += 1;

  }


}
public static void main(String args[]) {
    int i, j;
    // double sum = 0, square = 0, result = 0;
    Scanner s = new Scanner(System.in);
    int dimension = s.nextInt();

    int[][] spiral = new int[dimension][dimension];
    for (i = 0; i < dimension ; i++) {
        // loop for columns
        for (j = 0; j < dimension ; j++) {
            // reads the matrix elements
            spiral[i][j] = s.nextInt();
        }
    }
    spiral_method(spiral, dimension,dimension);
}
}
