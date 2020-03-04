interface Madar
	{	 
	}

interface RepuloMadar 
	{
	abstract void repul ();
	}

class Sas  implements RepuloMadar
	{
	public void repul ()
		{
		System.out.println("Repülés");
		}
	}

class Pingvin implements Madar
	{
	}

class Liskovhelyes
	{
	public static void main(String[] args) 
		{
		Sas sas=new Sas ();
		Pingvin pingvin=new Pingvin ();
		sas.repul ();
		pingvin.repul ();
		}
	}
