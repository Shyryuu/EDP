int divide(){
	
	if(rank()==root)
		*who.start=0; 

	else if(rank()==commsize()-1)
		*who.end=0;
	else
	{
		*who.start=rank()-1;
		*who.end=rank()+1;
	}

}