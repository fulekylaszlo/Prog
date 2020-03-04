class Killer
	{
	public void death ()
		{
		}
	};

class SerialKiller extends Killer
	{
	public void serialkillerdeath ()
		{
		}
	};

class Program
	{
	public static void main(String[] args)
		{
		Killer killer= new Killer ();
		SerialKiller serialkiller= new SerialKiller ();

		serialkiller.death ();
		serialkiller.serialkillerdeath ();

		killer.death ();

		//Az alsó sort kikommentelve, lefut a programunk, viszont ha nem kommenteljük ki, akkor ugyan olyan hibakódot kapunk
		// mint a C++ -os változatban.

		//killer.serialkiller();

		System.out.print("\"ÉÉéés hát itt is megjött a gyilkos. :O Javában is itt van :O\"");
		}
	};

