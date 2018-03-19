
int halo(int N, double M[],double R[],double S[],int mystart,int myend){

	int width,heigth,h=1,k=0;
	width=N;
	heigth=myend-mystart+1;


	if((commsize()%2)==0)// comprovamos si habrá algún procesador suelto
	{
		//primero enviamos de pares y recivimos de los impares 

		if (rank()%2==0)
			{	
				for (int jj= 0; jj<h; ++jj) // copiamos la última fila para poder enviarla 
				{
					for (int ii=0; ii<width; ++ii)
					{
						*(S+ii+jj*width)=*(M+ii+(jj+myend)*width);
					}	
			}

			checkr(MPI_Ssend(S,width*h,MPI_INT,rank()+1,0,MPI_COMM_WORLD),"sending" );

			MPI_Status st;
			checkr(MPI_Recv(R,width*h,MPI_INT,rank()+1,0,MPI_COMM_WORLD,&st),"receiving");	

				for (int jj = 0; jj<h; ++jj) // colocamos la información recivida por encima de la última fila
				{
					for (int ii=0; ii<width; ++ii)
					{
						*(M+ii+(jj+myend+1)*width)=*(R+ii+(jj)*width);
					}	
				}

			}

		else {

			MPI_Status st;
			checkr(MPI_Recv(R,width*h,MPI_INT,rank()-1,0,MPI_COMM_WORLD,&st),"receiving");

			for (int jj = 0; jj<h; ++jj) // copiamos la información que hemos recivido  en la primera fila
			{
				for (int ii=0; ii<width; ++ii)
				{
					*(M+ii+(jj)*width)=*(R+ii+(jj)*width);
				}	
			}
				
			for (int jj= 0; jj<h; ++jj) // copiamos la información que vamos a enviar de la fila 1
			{
				for (int ii=0; ii<width; ++ii)
				{
					*(S+ii+jj*width)=*(M+ii+(jj+h)*width);
				}	
			}

			checkr(MPI_Ssend(S,width*h,MPI_INT,rank()-1,0,MPI_COMM_WORLD),"sending" );
	
			}	

	if (commsize()>2){

		//primero enviamos de pares y recivimos de los impares 

			if (rank()%2!=0)
			{
				for (int jj= 0; jj<h; ++jj) // copiamos la última fila para poder enviarla 
				{
					for (int ii=0; ii<width; ++ii)
					{
						*(S+ii+jj*width)=*(M+ii+(jj+myend)*width);
					}	
				}

			checkr(MPI_Ssend(S,width*h,MPI_INT,rank()+1,0,MPI_COMM_WORLD),"sending" );

			MPI_Status st;
			checkr(MPI_Recv(R,width*h,MPI_INT,rank()+1,0,MPI_COMM_WORLD,&st),"receiving");	

				for (int jj = 0; jj<h; ++jj) // del vector R que mueve la información y lo ponemos en la última columna de la matriz M
				{
					for (int ii=0; ii<width; ++ii)
					{
						*(M+ii+(jj+myend+1)*width)=*(R+ii+(jj)*width);
					}	
				}	
			}
	
			else {

				MPI_Status st;
				checkr(MPI_Recv(R,width*h,MPI_INT,rank()-1,0,MPI_COMM_WORLD,&st),"receiving");

				for (int jj = 0; jj<h; ++jj) // copiamos la información que hemos recivido 
				{
					for (int ii=0; ii<width; ++ii)
					{
						*(M+ii+(jj)*width)=*(R+ii+(jj)*width);
					}	
				}
				
				for (int jj= 0; jj<h; ++jj) // copiamos la información que vamos a enviar 
				{
					for (int ii=0; ii<width; ++ii)
					{
						*(S+ii+jj*width)=*(M+ii+(jj+1)*width);
					}	
				}

				checkr(MPI_Ssend(S,width*h,MPI_INT,rank()-1,0,MPI_COMM_WORLD),"sending" );

			}
		} 
		else
			printf("Solo hay quants=%d procesadores\n",commsize());

		k=1;
	}

	else 
		{
			printf("Opción todavía no válida \n");
			k=0;
		}

	return k;
}