import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;

// ************************************* (1.) Tetris Class**************************************************************//
 public class TetrisBlock
{
    // Declaring all the properties of the generated Figures
    public int[][] shape;
    private Color color;
    private int x;
    private int y;
    private int[][][] shapes;
    private int currentRotation;

    TetrisBlock(int[][] shape, Color color) // Defining the shape and color of the blocks
    {
        this.shape = shape;
        this.color = color;
        initShapes();
    }
    // public void initShapes()  // Creaing a 3 dimensional array that will store the Shape(1st and 2nd D) and Rotation(3rd D) of the blocks
    // {
    //     shapes = new int[4][][];
    //     for(int i=0;i<4;i++)
    //     {
    //         int r = shape[0].length;
    //         int c = shape.length;
    //         shapes[i] = new int[r][c];
    //         for(int j=0;j<r;j++)
    //         {
    //             for(int k=0;k<c;k++)
    //             {
    //                 shapes[i][j][k] = shape[c-k-1][j];
    //             }
    //         }
    //         shape = shapes[i];
    //     }
    // }
    public void initShapes()
    {
        shapes = new int[4][][];
        for(int i=0;i<4;i++)
        {
            int c = shape[0].length;
            int r = shape.length;
            int m = r;
            shapes[i] = new int[c][r];
            for(int j=0;j<r;j++)
            {
                for(int k=0;k<c;k++)
                {
                    shapes[i][k][m-1] = shape[j][k];
                }
                m--;
            }
            shape = shapes[i];
        }
    }
    public void spawn(int gridWidth)
    {
        currentRotation = 0;
        shape = shapes[currentRotation]; // we must set this value before the set the x and y co-ordinates of the block.

        y = -getHeight(); // assign the y and x coordinates
        x = (gridWidth-getWidth())/2;
    }

    // Getters and Setters for all the respective attributes of the Figures
    public int[][] getShape()
    {
        return shape;
    }
    public Color getColor()
    {
        return color;
    }
    public int getWidth()
    {
        return shape[0].length;
    } // talking about length of first row
    public int getHeight()
    {
        return shape.length;
    }// length total no. of columns
    public int getX()
    {
        return x;
    }
    public int getY()
    {
        return y;
    }
    public void moveDown()
    {
        y++;
    }
    public void moveLeft()
    {
        if(x>0)
            x--;
    }
    public void moveRight(int sh[][])
    {
//        GamePanel obj=new GamePanel(10);
        if(x+sh[0].length<10)
            x++;
    }
    public int getBottomEdge()
    {
        return getY()+getHeight();
    }

    public void rotate()  // Method for Rotating a block
    {
        currentRotation++;
        if(currentRotation>3){currentRotation=0;}
        shape = shapes[currentRotation];
    }
}
