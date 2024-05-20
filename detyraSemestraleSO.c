#include<stdio.h>
#include<stdlib.h>
#include<math.h>
//perfshirja e librarise pthread.h
#include<pthread.h>

int arr[50], i;
int n;

//Erza Gashi
/*
average, minimum and maximum
vlerat do te ruhen globalisht
*/
float average;
int minimum;
int maximum;
float median;
float standard_deviation;

//Kaltrina Krasniqi
//thread1 per kalkulimin e average(mesatares)
void *th(){
	float sum = 0.0;
	for(i = 0 ; i < n ; i++)
		sum += arr[i];
	average = sum / n;
}

//Kaltrina Krasniqi
//thread2 per kalkulimin e vlerave minimale
void *th1(){
	minimum = arr[0];
	for(int i = 0 ; i < n ; i++)
		if(minimum > arr[i])
			minimum = arr[i];
}

//Erza Gashi
//thread3 per kalkulimin e vlerave maksimale
void *th2(){
	maximum = arr[0];
	for(int i = 0 ; i < n ; i++)
		if(maximum < arr[i])
			maximum = arr[i];
}


//Jon Kuçi
//thread4 per kalkulimin e medianes
void *th3(){
	//Se pari e sortojm vargun me selection sort
	int sorted_arr[50];
	for(int i = 0 ; i < n ; i++){
		sorted_arr[i] = arr[i];
	}
	
	for(int i = 0 ; i < n ; i++){
		int min_index = i;
		for(int j = i + 1 ; j < n ; j++){
			if(sorted_arr[j] < sorted_arr[min_index]){
				min_index = j;
			}
		}
		int temp = sorted_arr[min_index];
		sorted_arr[min_index] = sorted_arr[i];
		sorted_arr[i] = temp;
	}
	
	/*Nese gjatesia e varut esht qift gjej mesataren
	e dy numrave ne mes*/
	if(n % 2 == 0){
		median = (sorted_arr[n/2-1] + sorted_arr[n/2])/2.0;
		
	//nese gjatesia e vargut eshte tek, kthen anetarin ne mes
	} else {
		median = sorted_arr[n/2];
	}
}


//Jon Kuçi
//thread5 per kalkulimin e devidevijimit standard
void *th4(){
	//formula
	
	//mean = 1/n SUM(from i=0 to n-1) xi
	//variance = 1/n SUM(from i=0 to n-1) (xi - mean)^2
	//standard variation = square root of (variance)
	
	float sum = 0.0;
	
	for(int i = 0 ; i < n ; i++){
		sum += arr[i];
	}
	
	float mean = sum/n;
	
	float variance = 0.0;
	for(int i = 0 ; i < n ; i++){
		variance += (arr[i] - mean)*(arr[i] - mean);
	}
	
	variance /= (n);
	standard_deviation = sqrt(variance);
}


//Edon Gashi
int main(int argc, char *argv[]){
	int count = 0;
	/*
	seria e numrave te pasuar ne command line
	*/
	
	for(int i = 1 ; i < argc ; i++){
		arr[i - 1] = atoi(argv[i]);
		count++;
	}
	n = count;
	printf("%d command line argument are passed \n", count);
	
	for(int i = 0 ; i < n ; i++)
		printf("%d\t", arr[i]);
		
	printf("\n\n");
	
	int t, i;
	//pese objektet e punes se thread-ave jane t1, t2, t3, t4, t5
	pthread_t t1;
	pthread_t t2;
	pthread_t t3;
	pthread_t t4;
	pthread_t t5;
	
	//Krijimi i thread-ave
	t = pthread_create(&t1, NULL, &th, NULL);
	if((t) != 0){
		fprintf(stderr, "Krijimi i thread-it deshoi: %d\n", pthread_create(&t1, NULL, &th, NULL));
	}
	if((pthread_join(t1, NULL)) != 0){
		perror("pthread_join");
		return 1;
	}
	
	
	t = pthread_create(&t2, NULL, &th1, NULL);
	if((t) != 0){
	fprintf(stderr, "Krijimi i thread-it deshtoi: %d\n", pthread_create(&t2, NULL, &th1, NULL));
	}
	if((pthread_join(t2, NULL)) != 0){
		perror("pthread_join");
		return 1;
	}
	
	
	t = pthread_create(&t3, NULL, &th2, NULL);
	if((t) != 0){
		fprintf(stderr, "Krijimi i thread-it deshtoi: %d\n", pthread_create(&t3, NULL, &th2, NULL));
	}
	if((pthread_join(t3, NULL)) != 0){
		perror("pthread_join");
		return 1;
	}
	
	
	t = pthread_create(&t4, NULL, &th3, NULL);
	if((t) != 0){
		fprintf(stderr, "Krijimi i thread-it deshtoi: %d\n", pthread_create(&t4, NULL, &th3, NULL));
	}
	if((pthread_join(t4, NULL)) != 0){
		perror("pthread_join");
		return 1;
	}
	
	
	t = pthread_create(&t5, NULL, &th4, NULL);
	if((t) != 0){
		fprintf(stderr, "Krijimi i thread-it deshtoi: %d\n", pthread_create(&t5, NULL, &th4, NULL));
	}
	if((pthread_join(t5, NULL)) != 0){
		perror("pthread_join");
		return 1;
	}
	/*
	threadi prind do te shfaq te dhenat
	*/
	printf("\nThe average value is: %f", average);
	printf("\nThe Minimum value is: %d", minimum);
	printf("\nThe Maximum value is %d: ", maximum);
	printf("\nThe Median value is %f", median);
	printf("\nThe standard deviation is: %f", standard_deviation);
	printf("\n\n");
	
	return 0;
}
