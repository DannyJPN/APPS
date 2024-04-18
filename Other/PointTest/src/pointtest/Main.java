/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pointtest;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.canvas.Canvas;
import javafx.scene.layout.Pane;
import javafx.stage.Stage;

/**
 *
 * @author OEM
 */
public class Main extends Application {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        launch(args);
    }
    Canvas canvas;
      @Override
    public void start(Stage primaryStage) throws Exception {
        Pane root = new Pane();
        canvas = new Canvas(500, 500);
        primaryStage.setTitle("Tečky ");
        Scene scene = new Scene(root, 500, 500);
        primaryStage.setScene(scene);
        primaryStage.setResizable(true);
        primaryStage.show();
        root.getChildren().add(canvas);

         /*
        Point p1=new Point(50,120);
        Point p2=new Point (100,180);
        Point p3=new Point(120,260);
        Point p4= new Point (70,200);
        
        Point d12 = new Point(p2.x-p1.x,p2.y-p1.y);
        Point d34 = new Point(p3.x-p4.x,p3.y-p4.y);
        
        Point d23 = new Point(p3.x-p2.x,p3.y-p2.y);
        Point d14 = new Point(p4.x-p1.x,p4.y-p1.y);
        
        
        
        System.out.println("D12X: "+d12.x+"\tD12Y: "+d12.y);
        System.out.println("D34X: "+d34.x+"\tD34Y: "+d34.y);
        
         System.out.println("D23X: "+d23.x+"\tD23Y: "+d23.y);
        System.out.println("D14X: "+d14.x+"\tD14Y: "+d14.y);
        
        
        
       
        Display(p1.x,p1.y,p2.x,p2.y);
        Display(p2.x,p2.y,p3.x,p3.y);
        Display(p3.x,p3.y,p4.x,p4.y);
        Display(p4.x,p4.y,p1.x,p1.y);
        
        Display(p3.x,p3.y,p1.x,p1.y);
        Display(p2.x,p2.y,p4.x,p4.y);

*/
    Integer x =6;
    Integer y = x;
    x-=2;
     System.out.println(y);
        }
    
    
    private void drawPoint(int xPos, int yPos) {
        canvas.getGraphicsContext2D().strokeRect(xPos, yPos, 1, 1);
    }
    /*
    public  void Display(int x1,int y1 ,int x2 ,int y2 )
    {
        int x, y, dx, dy, p;
        //AbstPoint *abst;
        dx = x2 - x1;
        dy = y2 - y1;

    int origin = Octant(dx,dy);

        //System.out.println("Octant: "+origin);



        switch(origin)
        {
        case 1:
            {
            y = y1;
             p = 2 * dy - dx;         // prediktor

                for (x = x1; x <= x2; x++)
                {
                    //printf("X:%d\tY:%d\n",x,y);
                    drawPoint(x,y);
                    if (p >= 0)
                    {
                        y++;             // presun na dalsi radek
                        p = p + 2 * dy - 2 * dx;
                    }
                    else
                    {
                        p = p + 2 * dy;
                    }
                }

            break;


            }

        case 2:
            {
                x = x1;
                 p = 2 * dx - dy;         // prediktor

                for (y = y1; y <= y2; y++)
                {
                    //printf("X:%d\tY:%d\n",x,y);
                    drawPoint(x,y);
                    if (p >= 0)
                    {
                        x++;             // presun na dalsi radek
                        p = p + 2 * dx - 2 * dy;
                    }
                    else
                    {
                        p = p + 2 * dx;
                    }
                }





            break;
            }

        case 3:
            {
                x = x1;
                 p = -2 * dx - dy;         // prediktor

                for (y = y1; y <= y2; y++)
                {
                    //printf("X:%d\tY:%d\n",x,y);
                    drawPoint(x,y);
                    if (p >= 0)
                    {
                        x--;             // presun na dalsi radek
                        p = p - 2 * dx - 2 * dy;
                    }
                    else
                    {
                        p = p + -2 * dx;
                    }
                }
            break;
            }

        case 4:
            {
                 y = y1;
             p = 2 * dy + dx;         // prediktor

                for (x = x1; x >= x2; x--)
                {
                    //printf("X:%d\tY:%d\n",x,y);
                    drawPoint(x,y);
                    if (p >= 0)
                    {
                        y++;             // presun na dalsi radek
                        p = p + 2 * dy + 2 * dx;
                    }
                    else
                    {
                        p = p + 2 * dy;
                    }
                }

            break;
            }

        case 5:
            {
               y = y1;
             p = -2 * dy + dx;         // prediktor

                for (x = x1; x >= x2; x--)
                {
                    //printf("X:%d\tY:%d\n",x,y);
                    drawPoint(x,y);
                    if (p >= 0)
                    {
                        y--;             // presun na dalsi radek
                        p = p - 2 * dy + 2 * dx;
                    }
                    else
                    {
                        p = p - 2 * dy;
                    }
                }


            break;
            }

        case 6:
            {
               x = x1;
                 p = -2 * dx + dy;         // prediktor

                for (y = y1; y >= y2; y--)
                {
                    //printf("X:%d\tY:%d\n",x,y);
                    drawPoint(x,y);
                    if (p >= 0)
                    {
                        x--;             // presun na dalsi radek
                        p = p - 2 * dx + 2 * dy;
                    }
                    else
                    {
                        p = p - 2 * dx;
                    }
                }


            break;
            }

        case 7:
            {
                 x = x1;
                 p = 2 * dx + dy;         // prediktor

                for (y = y1; y >= y2; y--)
                {
                    //printf("X:%d\tY:%d\n",x,y);
                    drawPoint(x,y);
                    if (p >= 0)
                    {
                        x++;             // presun na dalsi radek
                        p = p + 2 * dx + 2 * dy;
                    }
                    else
                    {
                        p = p + 2 * dx;
                    }
                }



            break;
            }

        case 8:
            {
               y = y1;
             p = -2 * dy - dx;         // prediktor

                for (x = x1; x <= x2; x++)
                {
                    //printf("X:%d\tY:%d\n",x,y);
                    drawPoint(x,y);
                    if (p >= 0)
                    {
                        y--;             // presun na dalsi radek
                        p = p - 2 * dy - 2 * dx;
                    }
                    else
                    {
                        p = p - 2 * dy;
                    }
                }


            break;
            }




        }






    }*/
 public  void Display(int x1,int y1 ,int x2 ,int y2 )
    {
        Integer x, y, dx, dy, p;
        //AbstPoint *abst;
        dx = x2 - x1;
        dy = y2 - y1;

    int origin = Octant(dx,dy);

        //System.out.println("Octant: "+origin);

    y = y1;
             p = -2 * dy - dx;         // prediktor

                for (x = x1; x <= x2; x++)
                {
                    //printf("X:%d\tY:%d\n",x,y);
                    drawPoint(x,y);
                    if (p >= 0)
                    {
                        y--;             // presun na dalsi radek
                        p = p - 2 * dy - 2 * dx;
                    }
                    else
                    {
                        p = p - 2 * dy;
                    }
                }



       






    }


    int Octant(int x,int y)
    {
        if(Math.abs(x)> Math.abs(y))
        {
            //1,4,5,8
            if(x>=0 && y>=0)
            {
                return 1;
            }
            else if(x<0 && y>=0)
            {
                return 4;
            }
            else if(x<0 && y<0)
            {
                return 5;
            }
            else if(x>=0 && y<0)
            {
                return 8;
            }


        }
        else
        {
            //2,3,6,7
            if(x>=0 && y>=0)
            {
                return 2;
            }
            else if(x<0 && y>=0)
            {
                return 3;
            }
            else if(x<0 && y<0)
            {
                return 6;
            }
            else if(x>=0 && y<0)
            {
                return 7;
            }

        }
        return 0;

    }

    
}