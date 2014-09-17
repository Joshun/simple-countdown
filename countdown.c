#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SECONDS_IN_DAY (60*60*24)
#define SECONDS_IN_HOUR (60*60)
#define SECONDS_IN_MINUTE 60

void processArgs(struct tm *inputTime, int argc, char **argv)
{
	if( argc < 5 ) {
		printf("Usage: countdown <hour:minute:second> <day> <month> <year>\n");
		exit(EXIT_FAILURE);
	}
	else {
		int hour, minute, second;
		int day, month, year;
		sscanf(argv[1], "%d:%d:%d", &hour, &minute, &second);
		day = atoi(argv[2]);
		month = atoi(argv[3]);
		year = atoi(argv[4]);
		printf("Time input: %d:%d:%d\n", hour, minute, second);
		printf("Date input: %d/%d/%d\n", day, month, year);
		
		inputTime->tm_hour = hour;
		inputTime->tm_min = minute;
		inputTime->tm_sec = second;
		inputTime->tm_mday = day;
		inputTime->tm_mon = month - 1;
		inputTime->tm_year = year - 1900;
	}
}
void showTime(int seconds, int minutes, int hours, int days)
{
	printf((days == 1) ? "1 day\n" : "%d days\n", days);
	printf((hours == 1) ? "...and 1 hour\n" : "...and %d hours\n", hours);
	printf((minutes == 1) ? "...and 1 minute\n" : "...and %d minutes\n", minutes);
	printf((seconds == 1) ? "...and 1 second\n" : "...and %d seconds\n", seconds);
	//printf("%d days\n", days);
	//printf("...and %d hours\n", hours);
	//printf("...and %d minutes\n", minutes);
	//printf("...and %d seconds\n", seconds);
}

int main(int argc, char **argv)
{
	//Timeset futureTimeInput;
	//printf("Enter minute, hour, day, month, year:");
	//fscanf(stdin, "%d %d %d %d %d", &futureTimeInput.min, &futureTimeInput.hour, &futureTimeInput.day, &futureTimeInput.mon, &futureTimeInput.year);
	time_t currentTime = time(NULL);
	time_t futureTime;
	struct tm currentTimeBreakdown = *localtime(&currentTime);
	struct tm futureTimeBreakdown;
	//futureTimeBreakdown.tm_min = 10;
	//futureTimeBreakdown.tm_hour = 10;
	
	processArgs(&futureTimeBreakdown, argc, argv);
	futureTime = mktime(&futureTimeBreakdown);
	
	time_t timediff = difftime(futureTime, currentTime);
	
	if( timediff < 0 ) {
		printf("Cannot have time/date in past!\n");
		exit(EXIT_FAILURE);
	}
	
	printf("Future time: %s", asctime(&futureTimeBreakdown));
	printf("Current time: %s", asctime(&currentTimeBreakdown));
	printf("Time difference: %ld secs\n", (long)timediff);
	printf("Equal to:\n");
	int days = timediff / SECONDS_IN_DAY;
	int hours = (timediff - ((int)days * SECONDS_IN_DAY)) / SECONDS_IN_HOUR;
	int minutes = (timediff - ((int)days * SECONDS_IN_DAY) - ((int)hours * SECONDS_IN_HOUR)) / SECONDS_IN_MINUTE;
	int seconds = (timediff - ((int)days * SECONDS_IN_DAY) - ((int)hours * SECONDS_IN_HOUR) - ((int) minutes * SECONDS_IN_MINUTE));

	
	int countdownReached = 0;
	while( ! countdownReached ) {
		showTime(seconds, minutes, hours, days);
		sleep(1);
		if( seconds > 0 ) {
			seconds--;
		}
		else { 
			seconds = 59;
			if( minutes > 0 ) {
				minutes--;
			}
			else {
				minutes = 59;
				if( hours > 0) {
					hours--;
				}
				else {
					hours = 23;
					if( days > 0) {
						days--;
					}
				}
			}
		}
	}
	
	return 0;
}
	
