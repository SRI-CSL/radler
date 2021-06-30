/*
    BeepBeep, an event stream processor
    Copyright (C) 2008-2016 Sylvain Hallé

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

import static ca.uqac.lif.cep.Connector.INPUT;
import static ca.uqac.lif.cep.Connector.LEFT;
import static ca.uqac.lif.cep.Connector.OUTPUT;
import static ca.uqac.lif.cep.Connector.RIGHT;
import static ca.uqac.lif.cep.Connector.connect;
import ca.uqac.lif.cep.Pullable;
import ca.uqac.lif.cep.functions.BinaryFunction;
import ca.uqac.lif.cep.functions.ApplyFunction;
import ca.uqac.lif.cep.tmf.Fork;
import ca.uqac.lif.cep.tmf.QueueSource;
import ca.uqac.lif.cep.tmf.Trim;

/**
 * Calculate the Euclidean distance of each two successive points in an
 * input trace of (x,y) coordinates. For two points (<i>x</i><sub>1</sub>,<i>y</i><sub>1</sub>)
 * and  (<i>x</i><sub>2</sub>,<i>y</i><sub>2</sub>), the Euclidean distance is
 * defined as the square root of (<i>x</i><sub>1</sub>-<i>x</i><sub>2</sub>)<sup>2</sup> +
 * (<i>y</i><sub>1</sub>-<i>y</i><sub>2</sub>)<sup>2</sup>. The chain of
 * processors in this example can be represented graphically as:
 * <p>
 * <img src="{@docRoot}/doc-files/basic/PointDistance.png" alt="Processor graph">
 * <p>
 * In this picture, light green pipes correspond to streams of {@link Point}
 * objects. The processor with a ruler and a "d" is the {@link Distance}
 * processor defined below.
 * <p>
 * On an input stream made of points (2,7), (1,8), (2,8), (1,8), &hellip;, the
 * expected output of this program should look like:
 * <pre>
 * 1.4142135
 * 1.0
 * 1.0
 * 1.0
 * 3.6055512
 * &hellip;
 * </pre>
 * 
 * @author Sylvain Hallé
 * @difficulty Easy
 */
public class PointDistance
{
	/* We create a new type of event: Point. A point is just
	 * an "x" and a "y" value. This shows that in BeepBeep, anything can be an
	 * event, including user-defined objects. */
	public static class Point
	{
		public float x;
		public float y;

		public Point(float x, float y)
		{
			this.x = x;
			this.y = y;
		}
	}

	/**
	 * We create a new function: Distance. This function takes two points
	 * as its input, and returns their Euclidean distance as its output.
	 * It is therefore a 2:1 function.
	 * 
	 * @see functions.AddNumbers#AddNumbers()
	 */
	public static class Distance extends BinaryFunction<Point,Point,Float>
	{
		public Distance()
		{
			super(Point.class, Point.class, Float.class);
		}

		@Override
		public Float getValue(Point p1, Point p2)
		{
			return (float) Math.sqrt(Math.pow(p1.x - p2.x, 2) + Math.pow(p1.y - p2.y, 2));
		}
	}

	/*
	 *  A small main to illustrate the concept. 
	 */
	public static void main(String[] args)
	{
		/* Create a new source made of arbitrary Point objects. */
		QueueSource point_source = new QueueSource(1);
		point_source.setEvents(getListOfPoints());
		
		/* Duplicate the output of source along two paths. */
		Fork fork = new Fork(2);
		connect(point_source, OUTPUT, fork, INPUT);
		
		/* The first path is plugged directly as the first argument of a 
         * function processor that computes the Euclidean distance between
         * two points. */
		ApplyFunction distance_proc = new ApplyFunction(new Distance());
		connect(fork, LEFT, distance_proc, LEFT);
		
		/* The second path is trimmed of its first event... */
		Trim trim = new Trim(1);
		connect(fork, RIGHT, trim, INPUT);
		
		/* And is then plugged as the second input of the distance processor.
		 * This has for effect that distance_proc will compute the distance
		 * between each point and the next. */
		connect(trim, OUTPUT, distance_proc, RIGHT);

		/* Pull and print the first 10 events from the output. */
		Pullable p = distance_proc.getPullableOutput(OUTPUT);
		for (int i = 0; i < 10; i++)
		{
			float d = (Float) p.pull();
			System.out.println(d);
		}
	}

	public static void getPointDistance(float x1, float y1, float x2, float y2)
	{
		QueueSource point_source = new QueueSource(1);
		point_source.setEvents(new Object[]{new Point(x1, y1), new Point(x2, y2)});
		
		Fork fork = new Fork(2);
		connect(point_source, OUTPUT, fork, INPUT);
		
		ApplyFunction distance_proc = new ApplyFunction(new Distance());
		connect(fork, LEFT, distance_proc, LEFT);
		
		Trim trim = new Trim(1);
		connect(fork, RIGHT, trim, INPUT);
		
		connect(trim, OUTPUT, distance_proc, RIGHT);

		Pullable p = distance_proc.getPullableOutput(OUTPUT);
		for (int i = 0; i < 1; i++)
		{
			float d = (Float) p.pull();
			System.out.println(d + " <- (" + x1 + "," + y1 + ") (" + x2 + "," + y2 +")");
		}
	}

	/**
	 * Creates a dummy array of points
	 * @return An array of points
	 */
	public static Object[] getListOfPoints()
	{
		return new Object[]{
				new Point(2, 7),
				new Point(1, 8),
				new Point(2, 8),
				new Point(1, 8),
				new Point(2, 8),
				new Point(4, 5),
				new Point(9, 0),
				new Point(4, 5),
				new Point(2, 3),
				new Point(5, 3),
				new Point(6, 0),
				new Point(2, 8)
		};
	}
}
