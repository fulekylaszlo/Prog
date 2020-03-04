 class Madar
	{
	 void repul()
		{
		System.out.println("Reptetés");
		}
	}

class Sas extends Madar
	{
	@Override
	void repul()
		{
		System.out.println("Repül is");
		}
	}

class Pingvin extends Madar
	{
	}

class Liskov
	{
	public static void main(String[] args) 
		{
		Madar madar=new Madar ();
		madar.repul ();
		madar=new Sas ();
		madar.repul ();
		madar=new Pingvin ();
		madar.repul ();
		}
	}
