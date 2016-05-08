//http://wiki.osdev.org/CMOS

#include <system.h>
#define CURRENT_YEAR        2014                            // Change this each year!
 
int century_register = 0x00;                                // Set by ACPI table parsing code if possible
 
unsigned char second;
unsigned char minute;
unsigned char hour;
unsigned char day;
unsigned char month;
unsigned int year;
 
void out_byte(int port, int value);
int in_byte(int port);
 
enum {
      cmos_address = 0x70,
      cmos_data    = 0x71
};
 
int get_update_in_progress_flag() {
      outportb(cmos_address, 0x0A);
      return (inportb(cmos_data) & 0x80);
}
 
unsigned char get_RTC_register(int reg) {
      outportb(cmos_address, reg);
      return inportb(cmos_data);
}
 
void read_rtc() {
      unsigned char century = 0;
      unsigned char last_second;
      unsigned char last_minute;
      unsigned char last_hour;
      unsigned char last_day;
      unsigned char last_month;
      unsigned char last_year;
      unsigned char last_century;
      unsigned char registerB;
 
      // Note: This uses the "read registers until you get the same values twice in a row" technique
      //       to avoid getting dodgy/inconsistent values due to RTC updates
 
      while (get_update_in_progress_flag());                // Make sure an update isn't in progress
      second = get_RTC_register(0x00);
      minute = get_RTC_register(0x02);
      hour = get_RTC_register(0x04);
      day = get_RTC_register(0x07);
      month = get_RTC_register(0x08);
      year = get_RTC_register(0x09);
      if(century_register != 0) {
            century = get_RTC_register(century_register);
      }
 
      do {
            last_second = second;
            last_minute = minute;
            last_hour = hour;
            last_day = day;
            last_month = month;
            last_year = year;
            last_century = century;
 
            while (get_update_in_progress_flag());           // Make sure an update isn't in progress
 
            second = get_RTC_register(0x00);
            minute = get_RTC_register(0x02);
            hour = get_RTC_register(0x04);
            day = get_RTC_register(0x07);
            month = get_RTC_register(0x08);
            year = get_RTC_register(0x09);
            if(century_register != 0) {
                  century = get_RTC_register(century_register);
            }
      } while( (last_second != second) || (last_minute != minute) || (last_hour != hour) ||
               (last_day != day) || (last_month != month) || (last_year != year) ||
               (last_century != century) );
 
      registerB = get_RTC_register(0x0B);
 
      // Convert BCD to binary values if necessary
 
      if (!(registerB & 0x04)) {
            second = (second & 0x0F) + ((second / 16) * 10);
            minute = (minute & 0x0F) + ((minute / 16) * 10);
            hour = ( (hour & 0x0F) + (((hour & 0x70) / 16) * 10) ) | (hour & 0x80);
            day = (day & 0x0F) + ((day / 16) * 10);
            month = (month & 0x0F) + ((month / 16) * 10);
            year = (year & 0x0F) + ((year / 16) * 10);
            if(century_register != 0) {
                  century = (century & 0x0F) + ((century / 16) * 10);
            }
      }
 
      // Convert 12 hour clock to 24 hour clock if necessary
 
      if (!(registerB & 0x02) && (hour & 0x80)) {
            hour = ((hour & 0x7F) + 12) % 24;
      }
 
      // Calculate the full (4-digit) year
 
      if(century_register != 0) {
            year += century * 100;
      } else {
            year += (CURRENT_YEAR / 100) * 100;
            if(year < CURRENT_YEAR) year += 100;
      }
}

void print_month (char month) {
      if (month == 1) puts("January");
      else if (month == 2) puts("Feburary");
      else if (month == 3) puts("March");
      else if (month == 4) puts("April");
      else if (month == 5) puts("May");
      else if (month == 6) puts("June");
      else if (month == 7) puts("July");
      else if (month == 8) puts("August");
      else if (month == 9) puts("September");
      else if (month == 10) puts("October");
      else if (month == 11) puts("November");
      else if (month == 12) puts("December");
}

void print_time() {
      read_rtc();
      print_int(hour);    putch(':');
      print_int(minute);  putch(':');
      print_int(second);
}

void print_date() {
      read_rtc();
      print_int(day);    putch('-');
      print_month(month);  putch('-');
      print_int(year);
}

void print_datetime() {
      read_rtc();
      print_int(day);    putch('-');
      print_month(month);  putch('-');
      print_int(year);
      putch(' ');
      print_int(hour);    putch(':');
      print_int(minute);  putch(':');
      print_int(second);
}