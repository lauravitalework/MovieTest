using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using Accord.Video.FFMPEG;
using System.IO;
using System.Numerics;
using System.Drawing.Imaging;
namespace MovieTest
{
    public class Movie
    {
        public String[] szDays;
        public String version = "";
        public String cotalkVersion = "";
        public String cotalkDir = "";
        String outDir = "E://MOVIES//";


        public int width;
        public int height;
        public Boolean adults;

        String colorTypeDesc;
        Color colorType;
        Color colorOtherType;
        Boolean rotate = true;
        double triangleBaseLength = (.345);/// 2;// .345;
        double triangleHeight = (1.10) / 2;//.95;
        double triangleBorderWidth = 5;//10;
        double circleHeadRadius = .16;
        double nameFontW = .12;
        int multBy = 100;
         
        double fileDurSecs = 60 * 60;// 60 * 15;// 60 * 60;// 60;
        Boolean started = false;
        int part = 1;
        int linePos = 0;
        String[] prevLine = null;
        List<String> fileNames = new List<string>();
        public String szfileNames = "";

        int random = new Random().Next();


        public Movie(String[] szDays1, String cotalkVersion1, String cotalkDir1,String movieDir,int w, int h, Boolean t, String ctd, Color ct, Boolean r)
        {
            szDays = szDays1;
            cotalkVersion = cotalkVersion1;
            cotalkDir = cotalkDir1;

            outDir = movieDir;
            rotate = r;
            width = w * multBy;
            height = h * multBy;
            adults = t;
            colorTypeDesc = ctd;
            colorOtherType = ct == Color.Red ? Color.Blue : Color.Red;
            colorType = ct; 
            version = DateTime.Now.Month.ToString().ToString() + DateTime.Now.Day.ToString() + DateTime.Now.Year.ToString()+"_"+random;


            foreach (String day in szDays)
            {
                String dataFile = cotalkDir + "DAYCOTALK_" + Program.szDay(day) + cotalkVersion + ".CSV";
                String fileName= "SF21_" + day;
                StreamReader sr = new StreamReader(dataFile);
                {
                    sr.ReadLine();
                    while ((!sr.EndOfStream))
                    {
                       ClassMovieMaker2(fileName, ref sr);
                    }
                }
                sr.Close();
            }


        }
        public void ClassMovieMaker2(String fileName, ref StreamReader sr)
        {
            DateTime currentTime = new DateTime();
            Dictionary<String, String[]> personPos = new Dictionary<string, string[]>();
            double fileDur = 0;
            VideoFileWriter vFWriter = new VideoFileWriter();
            var framRate = 40;
            try
            {
                String outputFileName = outDir + fileName + (rotate ? "" : "NO") + random + "ROTATE__fr_" + framRate +"_"+version+ "_PART" + part + ".avi";
                szfileNames = szfileNames + (szfileNames == "" ? "" : "|") + fileName + (rotate ? "" : "NO") + random + "ROTATE__fr_" + framRate + "_" + version + "_PART" + part + ".avi";

                vFWriter.Open(outputFileName, width, height, framRate, VideoCodec.MPEG4);
                {
                    linePos++;
                    if (prevLine != null)
                    {
                        if (!personPos.ContainsKey(prevLine[0]))
                            personPos.Add(prevLine[0], prevLine);

                        prevLine = null;
                    }
                    while ((!sr.EndOfStream))
                    {
                        String[] line = sr.ReadLine().Split(',');
                        if (line.Length > 4)
                        {
                            DateTime lineTime = DateTime.Parse(line[1]);
                            if (!started)
                            {
                                currentTime = lineTime;
                                started = true;
                            }
                            if (lineTime.CompareTo(currentTime) != 0 || lineTime.Millisecond != currentTime.Millisecond)
                            {
                                if(line[6].Trim()!="")
                                {
                                    bool stop = true;
                                }
                                drawTriangles(personPos, ref vFWriter, currentTime);
                                personPos = new Dictionary<string, string[]>();

                                if (fileDur > fileDurSecs)
                                {
                                    fileDur = 0;
                                    vFWriter.Close();
                                    part++;
                                    prevLine = line;
                                    break;
                                }

                                fileDur += .1;
                                currentTime = lineTime;
                            }

                            if (!personPos.ContainsKey(line[0]))
                                personPos.Add(line[0], line);
                        }
                    }

;
                }
                fileNames.Add(outputFileName);

            }
            catch (Exception e)
            {//24355 75000 6506
                linePos = linePos;

            }



        }
        public void drawTriangles(Dictionary<String, String[]> personPos, ref VideoFileWriter vFWriter, DateTime currentTime)
        {
            Bitmap bmp = new Bitmap(height, width, PixelFormat.Format24bppRgb);
            //Bitmap image = new Bitmap(width, height, PixelFormat.Format24bppRgb);

            Graphics g = Graphics.FromImage(bmp);
            g.Clear(Color.White);
            g.DrawString(currentTime.ToLongTimeString() + "." + currentTime.Millisecond, new Font("Times New Roman", 22.0f), Brushes.Black, width / 2, 50 + 20);

            foreach (String k in personPos.Keys)
            {
                Tuple<PointF, PointF, PointF, PointF, PointF, PointF, PointF> pd = getTrianglePoints(personPos[k], triangleBaseLength);
                drawLineTriangle(personPos[k], pd, ref g);
            }


            vFWriter.WriteVideoFrame(bmp);
            bmp.Dispose();
            g.Dispose();
        }
        public Tuple<PointF, PointF, PointF, PointF, PointF, PointF, PointF> getTrianglePoints(String[] line, double tb)
        {

            //LEFT
            float xl = float.Parse(line[11]);
            float yl = float.Parse(line[12]);
            PointF pl = new PointF(xl, yl);


            //RIGHT
            float xr = float.Parse(line[9]);
            float yr = float.Parse(line[10]);
            PointF pr = new PointF(xr, yr);

            //CENTER

            float xc = (xl + xr) / 2;
            float yc = (yl + yr) / 2;
            PointF pc = new PointF(xc, yc);

            float dx = (xr - xl) / 2;
            float dy = (yr - yl) / 2;

            double m = Math.Sqrt(dx * dx + dy * dy);
            float rescale = (float)((tb * 0.5) / m);

            float new_xl = xc - dx * rescale;
            float new_xr = xc + dx * rescale;

            float new_yl = yc - dy * rescale;
            float new_yr = yc + dy * rescale;

            PointF pln = new PointF((float)new_xl, (float)new_yl);
            PointF prn = new PointF((float)new_xr, (float)new_yr);

            //TOP
            PointF pt = getTriangleHead(pln, prn, pc, triangleHeight);

            //HEAD
            PointF ph = getTriangleHead(pln, prn, pc, triangleHeight + circleHeadRadius);

            //NAME
            PointF pn = getTriangleHead(pln, prn, pc, (triangleHeight / 2));

            //MIDDLE
            PointF pm = getTriangleHead(pln, prn, pc, (triangleHeight / 4));

            return new Tuple<PointF, PointF, PointF, PointF, PointF, PointF, PointF>(pln, prn, pc, pt, ph, pn, pm);

        }
        public Tuple<PointF, PointF, PointF, PointF, PointF, PointF, PointF> getTrianglePoints1(String[] line, double tb)
        {
            float x = float.Parse(line[2]);
            float y = float.Parse(line[3]);

            //LEFT
            float xl = float.Parse(line[11]);
            float yl = float.Parse(line[12]);
            PointF pl = new PointF(xl, yl);


            //RIGHT
            float xr = float.Parse(line[9]);
            float yr = float.Parse(line[10]);
            PointF pr = new PointF(xr, yr);

            //CENTER
            double m = (yr - yl) / (xr - xl);
            float xc = (float)((xl < xr ? xl : xr) + (Math.Abs(xr - xl) / 2));
            float yc = (float)((yl < yr ? yl : yr) + (Math.Abs(yr - yl) / 2));
            PointF pc = new PointF((float)xc, (float)yc);


            //NEW LEFT
            float xln = (float)(xc - tb * (Math.Sqrt(1 / (1 + (m * m)))));
            float yln = (float)(yc - (m * tb) * (Math.Sqrt(1 / (1 + (m * m)))));
            PointF pln = new PointF((float)xln, (float)yln);

            //NEW RIGHT
            float xrn = (float)(xc + tb * (Math.Sqrt(1 / (1 + (m * m)))));
            float yrn = (float)(yc + (m * tb) * (Math.Sqrt(1 / (1 + (m * m)))));
            PointF prn = new PointF((float)xrn, (float)yrn);

            //TOP
            PointF pt = getTriangleHead(pln, prn, pc, triangleHeight);

            //HEAD
            PointF ph = getTriangleHead(pln, prn, pc, triangleHeight + circleHeadRadius);

            //NAME
            PointF pn = getTriangleHead(pln, prn, pc, (triangleHeight / 2));

            //MIDDLE
            PointF pm = getTriangleHead(pln, prn, pc, (triangleHeight / 4));

            return new Tuple<PointF, PointF, PointF, PointF, PointF, PointF, PointF>(pln, prn, pc, pt, ph, pn, pm);
        }


        public PointF getTriangleHead(PointF pl, PointF pr, PointF pc, double h)
        {
            double hr = h / Math.Sqrt(Math.Pow((pc.Y - pr.Y), 2) + Math.Pow((pr.X - pc.X), 2));
            double dx = (pl.Y - pr.Y) / 2;
            double dy = (pr.X - pl.X) / 2;
            double nx = pc.X + dx * hr;
            double ny = pc.Y + dy * hr;

            return new PointF((float)nx, (float)ny);

        }
        public PointF getTriangleCircleHead(PointF pl, PointF pr, PointF pc, double h)
        {

            //(triangleBaseLength + (circleHeadRadius * 2)) - Math.Pow((pl.Y - pr.Y), 2) = Math.Pow((pl.X - pr.X), 2);
            double hr = h / Math.Sqrt(Math.Pow((pc.Y - pr.Y), 2) + Math.Pow((pr.X - pc.X), 2));
            double cr = triangleBaseLength / (triangleBaseLength + (circleHeadRadius * 2));
            if (pl.X < pr.X)
                pl.X = (float)(pl.X - (pl.X * cr));
            else
                pr.X = (float)(pr.X + -(pr.X * cr));

            if (pl.Y < pr.Y)
                pl.Y = (float)(pl.Y - (pl.Y * cr));
            else
                pr.Y = (float)(pr.Y + -(pr.Y * cr));

            double dx = (pl.Y - pr.Y) / 2;
            double dy = (pr.X - pl.X) / 2;
            double nx = pc.X + dx * hr;
            double ny = pc.Y + dy * hr;
            return getTriangleHead(pl, pr, pc, h + (circleHeadRadius * 2));

        }
        public void drawLineTriangle(String[] line, Tuple<PointF, PointF, PointF, PointF, PointF, PointF, PointF> ps, ref Graphics g)
        {
            String name = line[0].Trim();
            if (name.IndexOf("_ORIGINAL") >= 0)
                name = name.Replace("_ORIGINAL", "");
            if (name.IndexOf("_") >= 0)
                name = name.Substring(name.LastIndexOf("_") + 1);
            String type = line[6].Trim();
            Boolean talking = line[5].Trim() == "True";

            PointF pl = ps.Item1;
            PointF pr = ps.Item2;
            PointF pc = ps.Item3;
            PointF pt = ps.Item4; //getTriangleHead(pl, pr, pc, triangleHeight);
            PointF ph = ps.Item5;
            PointF pn = ps.Item6;
            PointF pm = ps.Item7;

            amplifyPoint(ref pl);
            amplifyPoint(ref pr);
            amplifyPoint(ref pc);
            amplifyPoint(ref pt);
            amplifyPoint(ref ph);
            amplifyPoint(ref pn);
            amplifyPoint(ref pm);
            /* 
            PointF pm = getTriangleHead(pl, pr, pc, (double)(triangleHeight/2.00)); //ph;
            PointF phc = getTriangleCircleHead(pl, pr, pc, (double)(triangleHeight + circleHeadRadius )); //ph;
             
            amplifyPoint(ref pm);
            amplifyPoint(ref phc);

            */
            Boolean adult = isAdult(name);
            //float namePos = ph.X - 35;

            Brush color1 = colorType == Color.Blue ? Brushes.Blue : Brushes.Red;
            Brush color2 = colorType != Color.Blue ? Brushes.Blue : Brushes.Red;

            if ((!adult) || adults)
            {
                //g.DrawLine(new Pen(Color.DarkGray, 20), pl, pr);
                //(adult ? Brushes.Green : line[6].Trim() == blueType ? Brushes.Blue : Brushes.Red)
                //g.DrawString("L", new Font("Times New Roman", 14.0f), Brushes.Black, pl.X, pl.Y + 5);
                //g.DrawString("R", new Font("Times New Roman", 14.0f), Brushes.Black, pr.X, pr.Y + 5);
                Pen pen = new Pen((adult ? Color.Green : line[6].Trim().ToUpper() == colorTypeDesc.ToUpper() ? colorType : colorOtherType), (float)triangleBorderWidth);
                Brush brush = (adult ? Brushes.Green : line[6].Trim().ToUpper() == colorTypeDesc.ToUpper() ? color1 : color2);

                g.DrawPolygon(pen, new PointF[] { pl, pt, pr, pm });
                //g.FillEllipse(brush, ph.X, ph.Y, (float)(circleHeadRadius * 200), (float)(circleHeadRadius * 200));
                if (talking)
                {
                    g.FillPolygon((adult ? Brushes.Green : line[6].Trim().ToUpper() == colorTypeDesc.ToUpper() ? color1 : color2), new PointF[] { pl, pt, pr, pm });
                }
                g.DrawString(name, new Font("Times New Roman", 16.0f, FontStyle.Bold), Brushes.Black, pn.X, pn.Y);

            }
        }

        public Boolean isAdult(String k)
        {
            return (k.StartsWith("L") || k.StartsWith("T") || k.Contains("_T") || k.Contains("_L"));//FIX

        }
        public void amplifyPoint(ref PointF p)
        {
            p.X = p.X * multBy;
            p.Y = height - (p.Y * multBy);
        }


    }
}
