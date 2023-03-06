#ifndef GLCD_INTERFACE_H_
#define GLCD_INTERFACE_H_

void GLCD_voidInit(void);
void GLCD_VoidSendCommand(u8 Copy_U8Command);
void GLCD_VoidSendData(u8 Copy_U8Data);
u8 GLCD_U8SendString(const s8* Copy_pchString);
void GLCD_voidSendNumber(u32 Copy_U32Number);
void GLCD_VoidClearAll(void);
u8 GLCD_V_Line(u8 Copy_U8StartPage, u8 Copy_U8EndPage, u8 Copy_U8Col);
u8 GLCD_H_Line(u8 Copy_U8StartCol, u8 Copy_U8EndCol, u8 Copy_U8Page);
u8 GLCD_U8PageSelection(u8 Copy_U8Page);
u8 GLCD_U8ColumnSelection(u8 Copy_U8Column);

#endif
