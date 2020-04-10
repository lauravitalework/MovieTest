 
	

﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace Approach
{
    class ApproachInfo
    {
        public double Mean = 0;
        public double Median = 0;
        public double Mode = 0;
        public double Range = 0;
        public double Variance = 0;
        public double StdDev = 0;

        List<double> approaches = new List<double>();



        public void addValues(double a)
        {
            approaches.Add(a);
        }
        public void getValues()
        {
            double totalApproach = 0;
            foreach (double a in approaches)
            {
                totalApproach += a;
            }
            if (approaches.Count != 0)
            {
                Mean = totalApproach / approaches.Count;
                int HalfIndex = approaches.Count() / 2;
                var sortedapproaches = approaches.OrderBy(i => i);

                Mode = approaches.GroupBy(i => i).
                    OrderByDescending(n => n.Count()).
                    Select(n => n.Key).FirstOrDefault();

                double RangeMin = sortedapproaches.Min();
                double RangeMax = sortedapproaches.Max();
                Range = Math.Abs(RangeMax - RangeMin);


                Variance = approaches.Select(i => (i - Mean) * (i - Mean)).Sum();
                StdDev = Math.Sqrt(Variance);

                if (approaches.Count % 2 == 0)
                {
                    Median = ((sortedapproaches.ElementAt(HalfIndex) + sortedapproaches.ElementAt(HalfIndex - 1))) / 2;

                }
                else
                {
                    Median = sortedapproaches.ElementAt(HalfIndex);
                }

            }

        }

    }
    class ApproachesInfo
    {
        public ApproachInfo TotalInfo = new ApproachInfo();
        public ApproachInfo PosInfo = new ApproachInfo();
        public ApproachInfo NegInfo = new ApproachInfo();


    }
    class Program
    {
       
        public void getMinApproach(String byTimeType, String displayTimeType, String path, String fileVersion, String szDay)
        {
            String filePath = path + szDay + fileVersion;
                //"/Volumes/My Passport/APPROACH/PRIDE_LEAP/approach_trunk_5_30_2019_7_24_2019_2041261642.CSV";

            Dictionary<String, Dictionary<String, ApproachesInfo>> approachMinute = new Dictionary<string, Dictionary<String, ApproachesInfo>>();


            using (StreamReader sr = new StreamReader(filePath))
            {
                sr.ReadLine();
                while ((!sr.EndOfStream))// && lineCount<10000)
                {
                    String commaLine = sr.ReadLine();
                    String[] columns = commaLine.Split(',');
                    if (columns.Length > 6)
                    {
                        String person1 = columns[0];
                        String person2 = columns[1];
                        DateTime time = DateTime.Parse(columns[2]);
                        String szTime = "";

                        
                        
                        if (byTimeType == "SEC")
                        {
                            szTime = time.ToShortDateString() + " " + time.ToShortTimeString();
                            szTime = szTime.Replace(" AM", ":" + time.Second + " AM").Replace(" PM", ":" + time.Second + " PM");
                        }
                        else if (byTimeType == "MIN")
                        {
                            szTime = time.ToShortDateString() + " " + time.ToShortTimeString();
                        }
                        else
                        {
                            szTime = time.ToShortDateString();
                        }
                        double approach = Convert.ToDouble(columns[6]);
                        String pair = person1 + "|" + person2;

                        if (!approachMinute.ContainsKey(pair))
                            approachMinute.Add(pair, new Dictionary<String, ApproachesInfo>());

                        ApproachInfo pairInfo = new ApproachInfo();

                        if (!approachMinute[pair].ContainsKey(szTime))
                        {
                            ApproachesInfo Totalinfo = new ApproachesInfo();
                            approachMinute[pair].Add(szTime, new ApproachesInfo());


                        }
                        approachMinute[pair][szTime].TotalInfo.addValues(approach);

                        if (approach > 0)
                            approachMinute[pair][szTime].PosInfo.addValues(approach);
                        else
                            approachMinute[pair][szTime].NegInfo.addValues(approach);



                    }
                }
            }

            String todayVersion="_"+DateTime.Now.Month+"_"+ DateTime.Now.Day + "_"+DateTime.Now.Year + "_" +( new Random().Next());
            String outputFileName = "C:\\LVL\\approachesDATA_"+szDay+ todayVersion+"_TIME"+byTimeType+"_DISPLAY"+displayTimeType+".CSV";
            TextWriter approachPairs = new StreamWriter(outputFileName);// "approachesDATA_05_30_19perHOUR.csv");

            approachPairs.WriteLine("Person1,Person2, Time, " +
                "Mean, PosMean, NegMean, " +
                "Median, PosMedian, NegMedian, " +
                "Mode, PosMode, NegMode, " +
                "Range, PosRange, NegRange, " +
                "Variance, PosVariance, NegVariance, " +
                "StdDev, PosStdDev, NegStdDev ");

            int multForDisplay = displayTimeType == "SEC" ? 10 : (displayTimeType == "MIN" ? 600 : 36000);

            foreach (KeyValuePair<String, Dictionary<String, ApproachesInfo>> pairValue in approachMinute.OrderBy(i => i.Key))
            {
                String pair = pairValue.Key;
                foreach (String t in approachMinute[pair].Keys)
                {
                    approachMinute[pair][t].TotalInfo.getValues();
                    approachMinute[pair][t].PosInfo.getValues();
                    approachMinute[pair][t].NegInfo.getValues();

                    approachPairs.WriteLine(pair.Replace("|",",") + "," + t + "," +
                        approachMinute[pair][t].TotalInfo.Mean * multForDisplay + "," +////////////////
                        approachMinute[pair][t].PosInfo.Mean + "," +
                        approachMinute[pair][t].NegInfo.Mean + "," +
                        approachMinute[pair][t].TotalInfo.Median + "," +
                        approachMinute[pair][t].PosInfo.Median + "," +
                        approachMinute[pair][t].NegInfo.Median + "," +
                        approachMinute[pair][t].TotalInfo.Mode + "," +
                        approachMinute[pair][t].PosInfo.Mode + "," +
                        approachMinute[pair][t].NegInfo.Mode + "," +
                        approachMinute[pair][t].TotalInfo.Range + "," +
                        approachMinute[pair][t].PosInfo.Range + "," +
                        approachMinute[pair][t].NegInfo.Range + "," +
                        approachMinute[pair][t].TotalInfo.Variance + "," +
                        approachMinute[pair][t].PosInfo.Variance + "," +
                        approachMinute[pair][t].NegInfo.Variance + "," +
                        approachMinute[pair][t].TotalInfo.StdDev + "," +
                        approachMinute[pair][t].PosInfo.StdDev + "," +
                        approachMinute[pair][t].NegInfo.StdDev);


                }

                //approachPairs.WriteLine(pair + "," + pairApproaches[pair].Item1 + "," + pairApproaches[pair].Item2 + "," + (pairApproaches[pair].Item2 / pairApproaches[pair].Item1));
            }
             
        }
        //NOT RUN!!!!!
        public void getGeneralApproach()
        {
            String filePath = "/Volumes/My Passport/PRIDE_LEAP/PRIDE_LEAP_AM/SYNC/approach_trunk_1_23_2019_7_12_2019_1936293797.CSV";
            Dictionary<String, Dictionary<DateTime, double>> approaches = new Dictionary<string, Dictionary<DateTime, double>>();
            Dictionary<String, Tuple<double, double>> pairApproaches = new Dictionary<string, Tuple<double, double>>();

            using (StreamReader sr = new StreamReader(filePath))
            {
                sr.ReadLine();
                while ((!sr.EndOfStream))// && lineCount<10000)
                {
                    String commaLine = sr.ReadLine();
                    String[] columns = commaLine.Split(',');
                    if (columns.Length > 6)
                    {
                        String person1 = columns[0];
                        String person2 = columns[1];
                        DateTime time = DateTime.Parse(columns[2]);

                        int ms = Convert.ToInt16(columns[3]);
                        if (ms > 0)
                        {
                            bool stop = true;
                        }
                        time = time.AddMilliseconds(ms);
                        double approach = Convert.ToDouble(columns[6]);

                        String pair = person1 + "|" + person2;
                        if (!approaches.ContainsKey(pair))
                        {
                            approaches.Add(pair, new Dictionary<DateTime, double>());
                            pairApproaches.Add(pair, new Tuple<double, double>(0.1, approach));
                        }
                        else
                        {
                            Tuple<double, double> newvalues = new Tuple<double, double>(pairApproaches[pair].Item1 + 0.1, pairApproaches[pair].Item2 + approach);
                            pairApproaches[pair] = newvalues;
                            if (Double.IsNaN(newvalues.Item2))
                            {
                                bool stop = true;
                            }

                        }
                        if (!approaches[pair].ContainsKey(time))
                        {
                            approaches[pair].Add(time, approach);
                        }
                    }

                }
            }

            TextWriter approachPairs = new StreamWriter("approaches.csv");

            approachPairs.WriteLine("Pair, TotalTime, SumApproach, AvgApproach,");

            foreach (KeyValuePair<String, Tuple<double, double>> pairValue in pairApproaches.OrderBy(i => i.Key))
            {
                String pair = pairValue.Key;
                approachPairs.WriteLine(pair + "," + pairApproaches[pair].Item1 + "," + pairApproaches[pair].Item2 + "," + (pairApproaches[pair].Item2 / pairApproaches[pair].Item1));
            }
            Console.WriteLine("Finished!");
            Console.ReadLine();
        }
        static void Main(string[] args)
        {
            // String filePath = "/Volumes/My Passport/APPROACH/PRIDE_LEAP/approach_trunk_5_30_2019_7_24_2019_2041261642.CSV";

            String fileVeraion = "_7_31_2019_1777209647.CSV";// "_7_24_2019_2041261642.CSV";
            String filePath = "C:\\LVL\\approach_trunk_";
            //5_30_2019_7_24_2019_2041261642.CSV";
            String szDays = "2_20_2019";
            String[] days = szDays.Split(',');

            foreach(String szDay in days)
            {

                Program p = new Program();
                p.getMinApproach("DAY", "HOUR", filePath, fileVeraion, szDay);

            }





            Console.WriteLine("Finished!");
            Console.ReadLine();

        }
    }
}
 