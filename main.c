#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <math.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro_native_dialog.h>

char wtitle[50];
char namefproject[50];
double pos_x, pos_y,pos_x2, pos_y2;
bool done = FALSE, draw = FALSE,down = FALSE, fill = FALSE;
int r=0,g=0,b=0;
int width = 1280, height = 960;
int widx = 60, heix = 60;
float radius;
int gapx=0, txtgapx = 0;
int gapy=0;
ALLEGRO_BITMAP* icons[9];
ALLEGRO_BITMAP* save;
ALLEGRO_BITMAP* bmp;
ALLEGRO_BITMAP* load;
int brush_type = 0;
ALLEGRO_FONT *font ;
ALLEGRO_FONT *font2 ;
int punto = 28;
int punto2 = 20;
int thicknessi = 2;
char thickness[20];
bool saveb = TRUE;
ALLEGRO_DISPLAY *display = NULL;
short m_box(const char* message,
            const char* content_title,
            const char* title)
{

    switch(al_show_native_message_box(al_get_current_display(),
                                      title,
                                      content_title,
                                      message, NULL,
                                      ALLEGRO_MESSAGEBOX_YES_NO))
    {

    case 0:
        return 0; // User pressed the Cancel button
    case 1:
        return 1; //  "     "      "    OK     "
    case 2:
        return 2; // I don't understand what does this

    }
}
int collider (int x1, int y1, int x2, int y2, ALLEGRO_EVENT ev)
{

    pos_x = ev.mouse.x;
    pos_y = ev.mouse.y;





    if ((x2-1 > pos_x) && (x1+1 < pos_x) && (y2-1 > pos_y) && (y1+1 < pos_y) )
    {

        ///collision
        return 1;
    }
    /// no collision
    return 0;
}


void Draw_UI()
{


    itoa(thicknessi, thickness, 10);

    al_draw_filled_rectangle(0,0,widx/2, heix, al_map_rgb(100,100,100));
    al_draw_filled_rectangle(3,3,widx/2-3, heix-3, al_map_rgb(255,255,255));

    al_draw_filled_rectangle(widx/2-2,-2,widx+2, heix, al_map_rgb(100,100,100));
    al_draw_filled_rectangle(widx/2+2,2,widx-3, heix-3, al_map_rgb(255,255,255));

    al_draw_filled_rectangle(widx,0,width,heix,al_map_rgb(200,200,200));
    al_draw_filled_rectangle(0,heix,widx,height,al_map_rgb(200,200,200));

    /// Brush Type And Options Horizontal Bar
    ///Brush
    int x1, y1,x2, y2, sx;
    x1=60;
    y1 =13;
    x2=97;
    y2=50;

    gapy = (((width-widx)/2)-17.5)-120;

    if(thicknessi>9)
        txtgapx = 7;
    else
        txtgapx = 0;
    x1-=60;
    x2-=60;


    al_draw_filled_rectangle(width-45,15,width-15,45,al_map_rgb(100,100,100));
    al_draw_filled_rectangle(width-45+4,15+4,width-15-4,45-4,al_map_rgb(255,255,255));
    al_draw_text(font2,al_map_rgb(0,0,0), width-36, 20, NULL, "X");
    al_draw_filled_rectangle(x1+gapy,y1,x2+gapy,y2,al_map_rgb(100,100,100));
    if(brush_type!=6)
    {
        al_draw_filled_rectangle(x1+2+gapy,y1+2,x2-2+gapy,y2-2,al_map_rgb(255,255,255));

    }
    else
        al_draw_filled_rectangle(x1+2+gapy,y1+2,x2-2+gapy,y2-2,al_map_rgb(180,180,180));
    al_draw_bitmap(icons[6],x1+gapy+3,y1+1,NULL);
    x1-=60;
    x2-=60;

    al_draw_filled_rectangle(x1+gapy,y1,x2+gapy,y2,al_map_rgb(100,100,100));

    al_draw_filled_rectangle(x1+2+gapy,y1+2,x2-2+gapy,y2-2,al_map_rgb(255,255,255));

    al_draw_text(font,al_map_rgb(0,0,0), x1+gapy+10-txtgapx, y1+4, NULL, thickness);
    x1-=20;
    x2-=40;

    al_draw_filled_rectangle(x1+gapy,y1,x2+gapy,y2-19,al_map_rgb(100,100,100));
    al_draw_filled_rectangle(x1+2+gapy,y1+2,x2-2+gapy,y2-21,al_map_rgb(255,255,255));

    al_draw_filled_rectangle(x1+gapy,y1+22,x2+gapy,y2,al_map_rgb(100,100,100));
    al_draw_filled_rectangle(x1+2+gapy,y1+24,x2-2+gapy,y2-2,al_map_rgb(255,255,255));

    al_draw_text(font2,al_map_rgb(0,0,0), x1+gapy+3, y1-2, NULL, "+");

    al_draw_text(font2,al_map_rgb(0,0,0), x1+gapy+6, y1+17, NULL, "-");

    // al_draw_text(font2,al_map_rgb(0,0,0), 9,18,NULL,"L");
    al_draw_bitmap(icons[7],2,18,NULL);
    // al_draw_text(font2,al_map_rgb(0,0,0), 38,19,NULL,"S");
    al_draw_bitmap(icons[8],31,19,NULL);

    x1=60;
    y1 =13;
    x2=97;
    y2=50;

    al_draw_filled_rectangle(x1+gapy,y1,x2+gapy,y2,al_map_rgb(100,100,100));
    if(brush_type!=0)
        al_draw_filled_rectangle(x1+2+gapy,y1+2,x2-2+gapy,y2-2,al_map_rgb(255,255,255));
    else
        al_draw_filled_rectangle(x1+2+gapy,y1+2,x2-2+gapy,y2-2,al_map_rgb(180,180,180));
    al_draw_bitmap(icons[0],x1+gapy+3,y1+1,NULL);
    for(sx=0; sx<3; sx++)
    {
        x1+=60;
        x2+=60;

        al_draw_filled_rectangle(x1+gapy,y1,x2+gapy,y2,al_map_rgb(100,100,100));
        if(brush_type!=sx+1)
            al_draw_filled_rectangle(x1+2+gapy,y1+2,x2-2+gapy,y2-2,al_map_rgb(255,255,255));
        else
            al_draw_filled_rectangle(x1+2+gapy,y1+2,x2-2+gapy,y2-2,al_map_rgb(180,180,180));
        al_draw_bitmap(icons[sx+1],(float)(x1+gapy+3),y1+2,NULL);

    }
    x1+=60;
    x2+=60;
    al_draw_filled_rectangle(x1+gapy,y1,x2+gapy,y2,al_map_rgb(100,100,100));
    if(!(brush_type==4 || brush_type==5 ))
        al_draw_filled_rectangle(x1+2+gapy,y1+2,x2-2+gapy,y2-2,al_map_rgb(255,255,255));
    else
        al_draw_filled_rectangle(x1+2+gapy,y1+2,x2-2+gapy,y2-2,al_map_rgb(180,180,180));
    al_draw_bitmap(icons[sx+1],(float)(x1+gapy+3),y1+2,NULL);
    x1+=60;
    x2+=60;
    al_draw_filled_rectangle(x1+gapy,y1,x2+gapy,y2,al_map_rgb(100,100,100));
    if(!fill)
        al_draw_filled_rectangle(x1+2+gapy,y1+2,x2-2+gapy,y2-2,al_map_rgb(255,255,255));
    else
        al_draw_filled_rectangle(x1+2+gapy,y1+2,x2-2+gapy,y2-2,al_map_rgb(180,180,180));

    al_draw_bitmap(icons[sx+2],(float)(x1+gapy+3),y1+2,NULL);

    x1+=60;
    x2+=60;

    al_draw_filled_rectangle(x1+gapy,y1,x2+gapy,y2,al_map_rgb(100,100,100));
    al_draw_filled_rectangle(x1+2+gapy,y1+2,x2-2+gapy,y2-2,al_map_rgb(255,255,255));

    al_draw_text(font2,al_map_rgb(0,0,0), x1+gapy+11, y1+9,NULL, "C");


    /// Color Vertical Bar

    /**emerald*/
    al_draw_filled_rectangle(13+gapx,68,48+gapx,103,al_map_rgb(100,100,100));
    al_draw_filled_rectangle(13+2+gapx,68+2,48-2+gapx,103-2,al_map_rgb(0,138,0));

    /**green*/
    al_draw_filled_rectangle(13+gapx,108,48+gapx,143,al_map_rgb(100,100,100));
    al_draw_filled_rectangle(13+2+gapx,108+2,48-2+gapx,143-2,al_map_rgb(0,255,0));

    /**cyan*/
    al_draw_filled_rectangle(13+gapx,148,48+gapx,183,al_map_rgb(100,100,100));
    al_draw_filled_rectangle(13+2+gapx,148+2,48-2+gapx,183-2,al_map_rgb(27,161,226));

    /**blue*/
    al_draw_filled_rectangle(13+gapx,188,48+gapx,223,al_map_rgb(100,100,100));
    al_draw_filled_rectangle(13+2+gapx,188+2,48-2+gapx,223-2,al_map_rgb(0,0,255));

    /**indigo*/
    al_draw_filled_rectangle(13+gapx,228,48+gapx,263,al_map_rgb(100,100,100));
    al_draw_filled_rectangle(13+2+gapx,228+2,48-2+gapx,263-2,al_map_rgb(106,0,255));

    /**violet*/
    al_draw_filled_rectangle(13+gapx,268,48+gapx,303,al_map_rgb(100,100,100));
    al_draw_filled_rectangle(13+2+gapx,268+2,48-2+gapx,303-2,al_map_rgb(170,0,255));

    /**crimson*/
    al_draw_filled_rectangle(13+gapx,308,48+gapx,343,al_map_rgb(100,100,100));
    al_draw_filled_rectangle(13+2+gapx,308+2,48-2+gapx,343-2,al_map_rgb(162,0,37));

    /**red*/
    al_draw_filled_rectangle(13+gapx,348,48+gapx,383,al_map_rgb(100,100,100));
    al_draw_filled_rectangle(13+2+gapx,348+2,48-2+gapx,383-2,al_map_rgb(255,0,0));

    /**orange*/
    al_draw_filled_rectangle(13+gapx,388,48+gapx,423,al_map_rgb(100,100,100));
    al_draw_filled_rectangle(13+2+gapx,388+2,48-2+gapx,423-2,al_map_rgb(250,104,0));

    /**amber*/
    al_draw_filled_rectangle(13+gapx,428,48+gapx,463,al_map_rgb(100,100,100));
    al_draw_filled_rectangle(13+2+gapx,428+2,48-2+gapx,463-2,al_map_rgb(240,163,10));

    /**yellow*/
    al_draw_filled_rectangle(13+gapx,468,48+gapx,503,al_map_rgb(100,100,100));
    al_draw_filled_rectangle(13+2+gapx,468+2,48-2+gapx,503-2,al_map_rgb(255,255,0));

    /**gray */
    al_draw_filled_rectangle(13+gapx,508,48+gapx,543,al_map_rgb(50,50,50));
    al_draw_filled_rectangle(13+2+gapx,508+2,48-2+gapx,543-2,al_map_rgb(100,100,100));

    /**black*/
    al_draw_filled_rectangle(13+gapx,548,48+gapx,583,al_map_rgb(100,100,100));
    al_draw_filled_rectangle(13+2+gapx,548+2,48-2+gapx,583-2,al_map_rgb(0,0,0));





}

void Square(ALLEGRO_EVENT ev)
{

    if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {

        if(ev.mouse.button & 1)
        {
            pos_x = ev.mouse.x;
            pos_y = ev.mouse.y;

        }


    }


    if(ev.type ==  ALLEGRO_EVENT_MOUSE_BUTTON_UP)
    {
        if(ev.mouse.button & 1)
        {

            pos_x2 = ev.mouse.x;
            pos_y2 = ev.mouse.y;

            printf("%d , %d , %f \n", abs(pos_x2-pos_x), abs(pos_y2-pos_y), radius );
            if(pos_x2<widx)
                pos_x2 = widx;
            if(pos_y2<heix)
                pos_y2 = heix;
            if(pos_x<widx)
                pos_x = widx;
            if(pos_y<heix)
                pos_y = heix;


            radius = hypot(abs(pos_x2-pos_x), abs(pos_y2-pos_y));

            radius = sqrt(pow(radius, 2)/2);




            if(pos_x2>widx && pos_y2>heix || pos_x>widx && pos_y>heix)
            {

                if(!fill)
                {

                    if(pos_x < pos_x2 && pos_y < pos_y2)
                    {
						saveb = FALSE;
                        al_draw_rectangle(pos_x,pos_y,pos_x+radius,pos_y+radius,al_map_rgb(r,g,b),thicknessi);
                        
                    }

                    else if(pos_x < pos_x2 && pos_y > pos_y2)
                    {
                        saveb = FALSE;
                        al_draw_rectangle(pos_x,pos_y,pos_x+radius,pos_y-radius,al_map_rgb(r,g,b),thicknessi);
                    }

                    else if(pos_x > pos_x2 && pos_y > pos_y2)
                    {

                        saveb = FALSE;
                        al_draw_rectangle(pos_x,pos_y,pos_x-radius,pos_y-radius,al_map_rgb(r,g,b),thicknessi);
                    }

                    else if(pos_x > pos_x2 && pos_y < pos_y2)
                    {
                        al_draw_rectangle(pos_x,pos_y,pos_x-radius,pos_y+radius,al_map_rgb(r,g,b),thicknessi);
                        saveb = FALSE;
                    }

                }
                else
                {

                    if(pos_x < pos_x2 && pos_y < pos_y2)
                    {
                        saveb = FALSE;
                        al_draw_filled_rectangle(pos_x,pos_y,pos_x+radius,pos_y+radius,al_map_rgb(r,g,b));
                    }

                    else if(pos_x < pos_x2 && pos_y > pos_y2)
                    {
                        saveb = FALSE;
                        al_draw_filled_rectangle(pos_x,pos_y,pos_x+radius,pos_y-radius,al_map_rgb(r,g,b));

                    }

                    else if(pos_x > pos_x2 && pos_y > pos_y2)
                    {
                        saveb = FALSE;


                        al_draw_filled_rectangle(pos_x,pos_y,pos_x-radius,pos_y-radius,al_map_rgb(r,g,b));
                    }

                    else if(pos_x > pos_x2 && pos_y < pos_y2)
                    {
                        saveb = FALSE;

                        al_draw_filled_rectangle(pos_x,pos_y,pos_x-radius,pos_y+radius,al_map_rgb(r,g,b));
                    }



                }

            }

        }
    }

    Draw_UI();
    al_flip_display();


}

void Rec(ALLEGRO_EVENT ev)
{

    if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {

        if(ev.mouse.button & 1)
        {
            pos_x = ev.mouse.x;
            pos_y = ev.mouse.y;


        }


    }


    if(ev.type ==  ALLEGRO_EVENT_MOUSE_BUTTON_UP)
    {
        if(ev.mouse.button & 1)
        {

            pos_x2 = ev.mouse.x;
            pos_y2 = ev.mouse.y;

            printf("%d , %d , %f \n", abs(pos_x2-pos_x), abs(pos_y2-pos_y), radius );
            if(pos_x2<widx)
                pos_x2 = widx;
            if(pos_y2<heix)
                pos_y2 = heix;
            if(pos_x<widx)
                pos_x = widx;
            if(pos_y<heix)
                pos_y = heix;
            if(pos_x2>widx && pos_y2>heix || pos_x>widx && pos_y>heix)
            {


                if(!fill)
                {
                    saveb = FALSE;
                    al_draw_rectangle(pos_x,pos_y,pos_x2,pos_y2,al_map_rgb(r,g,b),thicknessi);
                }

                else
                {
                    saveb = FALSE;
                    al_draw_filled_rectangle(pos_x,pos_y,pos_x2,pos_y2,al_map_rgb(r,g,b));
                }

            }

        }
    }

    Draw_UI();
    al_flip_display();


}

void Triangle(ALLEGRO_EVENT ev)
{

    if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {

        if(ev.mouse.button & 1)
        {



            pos_x = ev.mouse.x;
            pos_y = ev.mouse.y;

        }


    }


    if(ev.type ==  ALLEGRO_EVENT_MOUSE_BUTTON_UP)
    {
        if(ev.mouse.button & 1)
        {

            pos_x2 = ev.mouse.x;
            pos_y2 = ev.mouse.y;

            printf("%d , %d , %f \n", abs(pos_x2-pos_x), abs(pos_y2-pos_y), radius );

            if(pos_x2<widx)
                pos_x2 = widx;
            if(pos_y2<heix)
                pos_y2 = heix;
            if(pos_x<widx)
                pos_x = widx;
            if(pos_y<heix)
                pos_y = heix;
            if(pos_x2>widx && pos_y2>heix || pos_x>widx && pos_y>heix)
            {
                if(!fill)
                {
                    saveb = FALSE;
                    al_draw_triangle(pos_x,pos_y,pos_x,pos_y2,pos_x2,pos_y2,al_map_rgb(r,g,b),thicknessi);
                }

                else
                {
                    saveb = FALSE;
                    al_draw_filled_triangle(pos_x,pos_y,pos_x,pos_y2,pos_x2,pos_y2,al_map_rgb(r,g,b));

                }

            }
        }
    }

    Draw_UI();
    al_flip_display();


}
void Circle(ALLEGRO_EVENT ev)
{

    if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {

        if(ev.mouse.button & 1)
        {
            pos_x = ev.mouse.x;
            pos_y = ev.mouse.y;

        }


    }


    if(ev.type ==  ALLEGRO_EVENT_MOUSE_BUTTON_UP)
    {
        if(ev.mouse.button & 1)
        {

            pos_x2 = ev.mouse.x;
            pos_y2 = ev.mouse.y;
            radius = hypot(abs(pos_x2-pos_x), abs(pos_y2-pos_y));
            printf("%d , %d , %f \n", abs(pos_x2-pos_x), abs(pos_y2-pos_y), radius );
            if(!fill)
            {
                al_draw_circle(pos_x,pos_y,radius,al_map_rgb(r,g,b),thicknessi);
                saveb = FALSE;
            }

            else
            {

                al_draw_filled_circle(pos_x,pos_y,radius,al_map_rgb(r,g,b));
                saveb = FALSE;
            }
        }
    }

    Draw_UI();
    al_flip_display();


}
void Line(ALLEGRO_EVENT ev)
{

    if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {

        if(ev.mouse.button & 1)
        {
            pos_x = ev.mouse.x;
            pos_y = ev.mouse.y;

        }


    }


    if(ev.type ==  ALLEGRO_EVENT_MOUSE_BUTTON_UP)
    {
        if(ev.mouse.button & 1)
        {
            pos_x2 = ev.mouse.x;
            pos_y2 = ev.mouse.y;
            if(pos_x2<widx)
                pos_x2 = widx;
            if(pos_y2<heix)
                pos_y2 = heix;
            if(pos_x<widx)
                pos_x = widx;
            if(pos_y<heix)
                pos_y = heix;
            if(pos_x2>widx && pos_y2>heix || pos_x>widx && pos_y>heix)
            {

                if(brush_type != 7)
                {
                    al_draw_line(pos_x,pos_y,pos_x2, pos_y2,al_map_rgb(r,g,b),thicknessi);
                    saveb = FALSE;
                }
                else
                {

                    if(abs(pos_x2-pos_x) >= abs(pos_y2-pos_y))
                    {
                        al_draw_line(pos_x,pos_y,pos_x2, pos_y,al_map_rgb(r,g,b),thicknessi);
                        saveb = FALSE;
                    }

                    else
                    {
                        saveb =FALSE;
                        al_draw_line(pos_x,pos_y,pos_x, pos_y2,al_map_rgb(r,g,b),thicknessi);

                    }






                }
            }

        }
    }

    Draw_UI();
    al_flip_display();


}
void Pencil(ALLEGRO_EVENT ev)
{

    if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {

        if(ev.mouse.button & 1)
        {
            pos_x = ev.mouse.x;
            pos_y = ev.mouse.y;
            pos_x2 = ev.mouse.x;
            pos_y2 = ev.mouse.y;
            draw = TRUE;
            down = TRUE;

        }
    }

    if(down)
    {
        pos_x = ev.mouse.x;
        pos_y = ev.mouse.y;
    }

    if(ev.type ==  ALLEGRO_EVENT_MOUSE_BUTTON_UP)
    {
        if(ev.mouse.button & 1)
        {

            draw = FALSE;
            down = FALSE;
        }
    }

    if(draw)
    {


        pos_x = ev.mouse.x;
        pos_y = ev.mouse.y;

        radius = thicknessi;
        if(brush_type != 6)
        {
            if(radius<7)
            {

                if(pos_x > widx-2 && pos_y > heix-2 && pos_x2 > widx-2 && pos_y2 > heix-2)
                {

                    saveb = FALSE;
                    al_draw_line(pos_x,pos_y,pos_x2,pos_y2,al_map_rgb(r,g,b),radius);
                }
            }
            else
            {

                if(pos_x > widx-2 && pos_y > heix-2 && pos_x2 > widx-2 && pos_y2 > heix-2)
                {

                    saveb = FALSE;
                    al_draw_filled_circle(pos_x,pos_y,radius,al_map_rgb(r,g,b));
                }

            }

        }
        else
        {
            if(radius<7)
            {

                if(pos_x > widx-2 && pos_y > heix-2 && pos_x2 > widx-2 && pos_y2 > heix-2)
                {
                    al_draw_line(pos_x,pos_y,pos_x2,pos_y2,al_map_rgb(255,255,255),radius);
                    saveb = FALSE;
                }

            }
            else
            {

                if(pos_x > widx-2 && pos_y > heix-2 && pos_x2 > widx-2 && pos_y2 > heix-2)
                {
                    al_draw_filled_circle(pos_x,pos_y,radius,al_map_rgb(255,255,255));
                    saveb = FALSE;
                }

            }


        }


        al_flip_display();
        pos_x2 = ev.mouse.x;
        pos_y2 = ev.mouse.y;


    }

    Draw_UI();

}
int main()
{



    if(!al_init())
        return -1;
    display = al_create_display(width, height);
    al_clear_to_color(al_map_rgb(255,255,255));

    al_install_mouse();
    al_install_keyboard();
    al_init_image_addon();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    font = al_load_ttf_font("arialbd.ttf",punto,0 );
    font2 = al_load_ttf_font("arial.ttf",punto2,0 );
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;

    event_queue = al_create_event_queue();
    al_register_event_source(event_queue,al_get_mouse_event_source());
    al_register_event_source(event_queue,al_get_display_event_source(display));
    al_register_event_source(event_queue,al_get_keyboard_event_source());


    strcpy(wtitle, "Paint - ");
    strcpy(namefproject, "Adsýz Proje");
    strcat(wtitle, namefproject);
    al_set_window_title(display,wtitle);




    icons[0] = al_load_bitmap("pencil.png");
    icons[1] = al_load_bitmap("line.png");
    icons[2] = al_load_bitmap("circle.png");
    icons[3] = al_load_bitmap("triangle.png");
    icons[4] = al_load_bitmap("rectangle.png");
    icons[5] = al_load_bitmap("fill.png");
    icons[6] = al_load_bitmap("eraser.png");
    icons[7] = al_load_bitmap("open.png");
    icons[8] = al_load_bitmap("save.png");

    ///DRAW APP UI
    Draw_UI();

    al_flip_display();
    /// UPDATE
    while(!done)
    {

        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        ///Select BrushType
        /// Pencil(ev);
        /// Line(ev);
        ///Circle(ev);
        /// Triangle(ev);
        ///Rec(ev);
        ///Square(ev);

        if(!saveb)
        {


            strcpy(wtitle, "Paint - ");
            strcat(wtitle, namefproject);
            strcat(wtitle, " *");
            al_set_window_title(display,wtitle);

        }
        else
        {



            strcpy(wtitle, "Paint - ");
            strcat(wtitle, namefproject);

            al_set_window_title(display,wtitle);


        }


        if(ev.type == ALLEGRO_EVENT_KEY_DOWN )
        {
            if(ev.keyboard.keycode == ALLEGRO_KEY_LSHIFT  )
            {
                if(brush_type == 4)
                    brush_type = 5;

            }
        }
        if(ev.type == ALLEGRO_EVENT_KEY_UP )
        {
            if(ev.keyboard.keycode == ALLEGRO_KEY_LSHIFT  )
            {
                if(brush_type == 5)
                    brush_type = 4;

            }
        }


        if(ev.type == ALLEGRO_EVENT_KEY_DOWN )
        {
            if(ev.keyboard.keycode == ALLEGRO_KEY_LSHIFT  )
            {
                if(brush_type == 1)
                    brush_type = 7;

            }
        }
        if(ev.type == ALLEGRO_EVENT_KEY_UP )
        {
            if(ev.keyboard.keycode == ALLEGRO_KEY_LSHIFT  )
            {
                if(brush_type == 7)
                    brush_type = 1;

            }
        }



        switch(brush_type)
        {
        case 0:
            Pencil(ev);
            break;
        case 1:
            Line(ev);
            break;
        case 2:
            Circle(ev);
            break;
        case 3:
            Triangle(ev);
            break;
        case 4:
            Rec(ev);
            break;
        case 5:
            Square(ev);
            break;
        case 6:
            Pencil(ev);
            break;
        case 7:
            Line(ev);
            break;
        default:
            Pencil(ev);


        }

        ///EXIT
        if(ev.type == ALLEGRO_EVENT_KEY_DOWN )
        {

            if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            {
                if(!saveb)
                {

                     switch(m_box("Kaydetmek istiyor musunuz?",
              "Yapilan degisiklikleri", "Kaydet?"))
                    {

                    case 0:
                        done=TRUE;
                        break;
                    case 1:
                        savefuc();
                        break;


                    }

                    done = TRUE;


                }
                else
                {
                    done = TRUE;


                }

            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_PAD_PLUS)
            {
                if(thicknessi<99)
                    thicknessi++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_PAD_MINUS)
            {

                if(thicknessi>1)
                    thicknessi--;
            }
            Draw_UI();
            al_flip_display();


        }
        /// BRUSH COLLIDER
        if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN || ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {

            ///Pencil  x1=60; y1 =13; x2=97; y2=50;

            if (collider(60+gapy,13,97+gapy,50, ev))
            {
                brush_type = 0;


            }
            else if (collider(120+gapy,13,157+gapy,50, ev))
            {
                brush_type = 1;
            }


            ///Circle
            else if (collider(180+gapy,13,217+gapy,50, ev))
            {
                brush_type =2;
            }


            ///Triangle
            else if (collider(180+60+gapy,13,217+60+gapy,50, ev))
            {
                brush_type = 3;
            }

            ///Rectangle
            else if (collider(180+120+gapy,13,217+120+gapy,50, ev))
            {
                brush_type = 4;

            }
            ///fill
            else if (collider(180+180+gapy,13,217+180+gapy,50, ev))
            {
                if(!fill)
                    fill=TRUE;
                else
                    fill = FALSE;

            }
            else if (collider(180+180+60+gapy,13,217+180+60+gapy,50, ev))
            {
                al_clear_to_color(al_map_rgb(255,255,255));

            }

            else if (collider(gapy,13,97-60+gapy,50, ev))
            {
                brush_type = 6;

            }
            if (collider(gapy-80,36,97-160+gapy,50, ev))
            {
                if(thicknessi>1)
                    thicknessi--;

            }
            if (collider(gapy-80,13,97-160+gapy,29, ev))
            {
                if(thicknessi<99)
                    thicknessi++;
            }





            ///emerald
            else if (collider(15,70,46,101, ev))
            {

                r=0;
                g=138;
                b=0;
            }

            ///green
            else if (collider(15,110,46,141, ev))
            {

                r=0;
                g=255;
                b=0;
            }

            ///cyan
            else if (collider(15,150,46,181, ev))
            {

                r=27;
                g=161;
                b=226;
            }

            ///blue
            else if (collider(15,190,46,221, ev))
            {

                r=0;
                g=0;
                b=255;
            }

            ///indigo
            else if (collider(15,230,46,261, ev))
            {

                r=106;
                g=0;
                b=255;
            }

            ///violet
            else if (collider(15,270,46,301, ev))
            {

                r=170;
                g=0;
                b=255;
            }

            ///crimson
            else if (collider(15,310,46,341, ev))
            {

                r=162;
                g=0;
                b=37;
            }

            ///red
            else if (collider(15,350,46,381, ev))
            {

                r=255;
                g=0;
                b=0;
            }

            ///orange
            else if (collider(15,390,46,421, ev))
            {

                r=250;
                g=104;
                b=0;
            }

            ///amber
            else if (collider(15,430,46,461, ev))
            {

                r=240;
                g=163;
                b=10;
            }

            ///yellow
            else if (collider(15,470,46,501, ev))
            {

                r=255;
                g=255;
                b=0;
            }

            ///grey
            else if (collider(15,510,46,541, ev))
            {

                r=100;
                g=100;
                b=100;
            }

            ///black
            else if (collider(15,550,46,581, ev))
            {

                r=0;
                g=0;
                b=0;
            }

            else if (collider(29,1,58,58, ev))
            {

                ALLEGRO_FILECHOOSER* savefile = al_create_native_file_dialog(NULL, "Kayýt konumunu ve ismini seçin", "*.bmp*;*.jpg*;*.png*;", ALLEGRO_FILECHOOSER_SAVE );
                al_show_native_file_dialog(NULL,savefile);
                const char* path0 = al_get_native_file_dialog_path(savefile,0);





                if(path0 != NULL)
                {

                    char *charray = NULL;
                    charray = path0;

                    int i;

                    for( i=0; i<strlen(charray); i++)
                    {
                        if(*(charray+i)== '.')
                            break;


                    }
                    if(i == strlen((charray)))
                    {

                        int leng = strlen(charray);
                        (*(charray+leng)) = '.';
                        (*(charray+leng+1)) = 'j';
                        (*(charray+leng+2)) = 'p';
                        (*(charray+leng+3)) = 'g';
                        (*(charray+leng+4)) = '\0';
                        path0 = charray;


                    }
                    int lastap=0;
                    for( i=0; i<strlen(charray); i++)
                    {
                        if(*(charray+i)== '\\')
                            lastap = i;


                    }

                    bmp = al_create_bitmap(width-widx,height-heix);
                    al_set_target_bitmap(bmp);
                    al_draw_bitmap_region(al_get_backbuffer(display),widx,heix,width-widx,height-heix,0,0,0);
                    al_save_bitmap(path0,bmp);
                    al_set_target_bitmap(al_get_backbuffer(display));

                    for(i=0; i<50; i++)
                        namefproject[i] = '\0';
                    for(i=0; i<50; i++)
                        wtitle[i] = '\0';

                    for(i = lastap-1; i<strlen(charray); i++)
                        namefproject[i-lastap-1] = charray[i];


                    strcpy(wtitle, "Paint --- ");
                    strcat(wtitle, namefproject);
                    al_set_window_title(display,wtitle);

                    saveb = TRUE;

                    //al_save_bitmap(path0,al_get_backbuffer(display));
                }
            }

            else if (collider(2,2,28,58, ev))
            {


                ALLEGRO_FILECHOOSER* loadfile = al_create_native_file_dialog (NULL, "Dosya Seçin", "*.bmp*;*.jpg*;*.png*;",ALLEGRO_FILECHOOSER_PICTURES  );
                al_show_native_file_dialog(NULL,loadfile);

                const char* path=al_get_native_file_dialog_path(loadfile,0);
                if(path != NULL)
                {

                    load = al_load_bitmap(path);
                    if(load != NULL)
                        al_draw_bitmap(load,widx,heix,NULL);
                }

                Draw_UI();
            }

            else if (collider(width-45,15,width-15,45, ev))
            {



                if(!saveb)
                {

                    switch(m_box("Kaydetmek istiyor musunuz?",
              "Yapilan degisiklikleri", "Kaydet?"))
                    {

                    case 0:
                        done=TRUE;
                        break;
                    case 1:
                        savefuc();
                        break;


                    }


                    done = TRUE;

                }
                else
                {
                    done = TRUE;


                }

            }


            Draw_UI();
            al_flip_display();

        }


    }

}


void savefuc()
{


    ALLEGRO_FILECHOOSER* savefile = al_create_native_file_dialog(NULL, "Kayýt konumunu ve ismini seçin", "*.bmp*;*.jpg*;*.png*;", ALLEGRO_FILECHOOSER_SAVE );
    al_show_native_file_dialog(NULL,savefile);
    const char* path0 = al_get_native_file_dialog_path(savefile,0);


    if(path0 != NULL)
    {

        char *charray = NULL;
        charray = path0;

        int i;

        for( i=0; i<strlen(charray); i++)
        {
            if(*(charray+i)== '.')
                break;


        }
        if(i == strlen((charray)))
        {

            int leng = strlen(charray);
            (*(charray+leng)) = '.';
            (*(charray+leng+1)) = 'j';
            (*(charray+leng+2)) = 'p';
            (*(charray+leng+3)) = 'g';
            (*(charray+leng+4)) = '\0';
            path0 = charray;


        }
        int lastap=0;
        for( i=0; i<strlen(charray); i++)
        {
            if(*(charray+i)== '\\')
                lastap = i;


        }






        bmp = al_create_bitmap(width-widx,height-heix);
        al_set_target_bitmap(bmp);
        al_draw_bitmap_region(al_get_backbuffer(display),widx,heix,width-widx,height-heix,0,0,0);
        al_save_bitmap(path0,bmp);
        al_set_target_bitmap(al_get_backbuffer(display));

        for(i=0; i<50; i++)
            namefproject[i] = '\0';
        for(i=0; i<50; i++)
            wtitle[i] = '\0';

        for(i = lastap-1; i<strlen(charray); i++)
            namefproject[i-lastap-1] = charray[i];


        strcpy(wtitle, "Paint --- ");
        strcat(wtitle, namefproject);
        al_set_window_title(display,wtitle);

        saveb = TRUE;

        //al_save_bitmap(path0,al_get_backbuffer(display));
    }




}
