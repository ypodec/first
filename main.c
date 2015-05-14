#include "pebble.h"

Window *window; 
TextLayer *text_layer; 

static void second_tick(struct tm* tick_time, TimeUnits units_changed) 
{
    static char time[] = "00:00:00"; 
    strftime(time, sizeof(time), "%T", tick_time); 
    text_layer_set_text(text_layer, time); /* пишем строку со временем в тестовый слой */
}

int main(void) 
{
    window = window_create(); 
    window_set_background_color(window, GColorBlack);  
    window_stack_push(window, true);
    text_layer = text_layer_create(GRect(0, 0, 144, 168)); 
    text_layer_set_text_color(text_layer, GColorWhite); 
    text_layer_set_background_color(text_layer, GColorClear); 
    text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
    text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
    layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer)); 
    time_t now = time(NULL); /* создаем переменную и пишем в нее POSIX-время */
    struct tm *current_time = localtime(&now); /* получаем из POSIX значения времени и даты */
    tick_timer_service_subscribe(SECOND_UNIT, &second_tick); /* подписываемся на секундный таймер */
    second_tick(current_time, SECOND_UNIT); /* вызываем обновление времени не дожидаясь тика */

    app_event_loop(); 

    text_layer_destroy(text_layer);
    window_destroy(window); 
    tick_timer_service_unsubscribe(); 

}
