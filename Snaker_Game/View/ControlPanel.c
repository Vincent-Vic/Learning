/******************************************************
    > File Name: ControlPanel.c
    > Author: Vincent??Vic
    > Mail: Vincent-Vic@qq.com
    > Created by Vincent Vic on 2018/3/27.
    > Functional Control Panel implementation
*******************************************************/

#include "ControlPanel.h"

//Control panel global pointer
Panel* control_panel=NULL;

//Control panel operation function, external call structure member, global definition.
ControlPanelOperator* controlPanelOperator=NULL;

/**
 * Control panel display information and options
 */
TextView Control_Panel_Views[]= {
        {5,3, 0xE,0x0,8,"Score :0", 0},
        {5,6, 0xE,0x0,8,"length:0", 0},
        {5,9, 0xE,0x0,8,"S / G :0.0", 0},
        {5,14,0x0,0xE,12,"Game Help",1},
        {5,16,0xE,0x0,12,"Games start",1},
        {5,18,0xE,0x0,12,"Game settings",1},
        {5,20,0xE,0x0,12,"Exit Game",1}
};

/**
 * Escape key processing event
 * @param v
 * @return void*
 */
void* Escape_Key_Press(char v);

/**
 * Return key processing event
 * @param v
 * @return void*
 */
void* Enter_Key_Press(char v);

/**
 * Get the number of components
 * @return int
 */
int getTextViewLen();

/**
 * Judge the selection component
 * @param len
 */
void ViewPanelSelected(int len);

/**
 * Upper direction processing event
 * @param v
 * @return void *
 */
void* Control_Panel_Up_Handler(char v);

/**
 * Down direction processing event
 * @param v
 * @return void*
 */
void* Control_Panel_Down_Handler(char v);

/**
 * Get Text View structure lenght
 * @return
 */
int getTextViewLen()
{
    return  sizeof(Control_Panel_Views) / sizeof(TextView);
}

/**
 * Display the corresponding panel according to the currently selected component
 * @param len
 */
void ViewPanelSelected(int len)
{
    if(NULL != controlPanelOperator){
        //Obtaining the selection function subscript
        int QueryIndex=QuerySelectView(Control_Panel_Views, len, control_panel->bgcolor);
        //Obtaining selection function information
        TextView* v=&Control_Panel_Views[QueryIndex];
        /**
         *The function of selection is judged, and different panels are toggle.
         */
        if(strcmp(v->txt, "Game Help")==0){
            if(controlPanelOperator->view_help_panel!=NULL){
                controlPanelOperator->view_help_panel();
            }
        }else if(strcmp(v->txt, "Games start")==0){
            if(controlPanelOperator->view_game_pancel!=NULL){
                controlPanelOperator->view_game_pancel();
            }
        }else if(strcmp(v->txt, "Game settings")==0){
            if(controlPanelOperator->view_setting_panel!=NULL){
                controlPanelOperator->view_setting_panel();
            }
        }else if(strcmp(v->txt, "Exit Game")==0){
            if(controlPanelOperator->view_exit_panel!=NULL){
                controlPanelOperator->view_exit_panel();
            }
        }
    }
}

void* Control_Panel_Up_Handler(char v)
{
    int len = getTextViewLen();
    //Change the selected view
    ChangeSelectedView(Control_Panel_Views,len,control_panel->bgcolor,control_panel->color,0);
    //Emergence
    drawView(control_panel,Control_Panel_Views,len);
    //Display the corresponding panel according to the currently selected component
    ViewPanelSelected(len);
    PlayGameSound("..\\Sound\\page.wav");
    Sleep(1000);
    StopGameSound();
}

void* Control_Panel_Down_Handler(char v)
{
    int len = getTextViewLen();
    //Change the selected view
    ChangeSelectedView(Control_Panel_Views,len,control_panel->bgcolor,control_panel->color,1);
    //Emergence
    drawView(control_panel,Control_Panel_Views,len);
    //Display the corresponding panel according to the currently selected component
    ViewPanelSelected(len);
    PlayGameSound("..\\Sound\\page.wav");
    Sleep(1000);
    StopGameSound();
}

void* Enter_Key_Press(char v)
{
    if(controlPanelOperator!=NULL && controlPanelOperator->start_game!=NULL){
        int len = getTextViewLen();
        ////Obtaining the selection function subscript
        int QueryIndex = QuerySelectView(Control_Panel_Views,len,control_panel->bgcolor);
        //If the vehicle is down, play on the game function option.
        if(QueryIndex==4){
            controlPanelOperator->start_game();
        }
        //If you return to press, set the panel function option and enter the set panel.
        if(QueryIndex==5){
            while(getSettingExit()!=1){
                Setting_Panel_Key_Bind();
            }
            InitialSettingControlInfo();
        }
        //If the vehicle is down, exit the program on the exit of the game function option.
        if(QueryIndex==6){
            exit(0);
        }
    }
}

void* Escape_Key_Press(char v)
{
    exit(0);
}

void drawControlPanel()
{
    if(control_panel==NULL)
    {
        control_panel=PanelInit();
        control_panel->x=2;
        control_panel->y=1;
        control_panel->Width=21;
        control_panel->Heigth=22;
        control_panel->color=0xE;
        control_panel->bgcolor=0x0;
    }
    drawPanel(control_panel);
    drawHline(control_panel->x+1,control_panel->y+12,control_panel->bgcolor<<4|control_panel->color,control_panel->HLetter,control_panel->Width-2);
    int View_len= sizeof(Control_Panel_Views)/ sizeof(TextView);
    drawView(control_panel,Control_Panel_Views,View_len);
}

void Control_Panel_Key_Bind()
{
    //Special key binding operation
    DefaultHandler handler={Control_Panel_Up_Handler,Control_Panel_Down_Handler};
    KeyMapping mappings[]={
            {13,Enter_Key_Press},
            {27,Escape_Key_Press}
    };
    int len= sizeof(mappings)/ sizeof(KeyMapping);
    Key_Handler_Operator(&handler,mappings,len);
}

void setControlPanelOperator(ControlPanelOperator *anOperator)
{
    controlPanelOperator = anOperator;
}

void setGameInfo(int score, int length, double speed)
{
    //Setting panel information
    char score_str [50];
    sprintf(score_str,"Score :%d",score);
    strcpy(Control_Panel_Views[0].txt,score_str);
    char len_str[50];
    sprintf(len_str,"length:%d",length);
    strcpy(Control_Panel_Views[1].txt,len_str);
    char speed_str[50];
    sprintf(speed_str,"S / G :%.2lf",speed);
    strcpy(Control_Panel_Views[2].txt,speed_str);
    drawControlPanel();
}
