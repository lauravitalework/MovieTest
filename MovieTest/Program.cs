using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using Accord.Video.FFMPEG;
namespace MovieTest
{
    class Program
    {
        public static String szDay(String szDay)
        {
            String szDay2 = "";
            String[] dayParts = szDay.Split('_');
            foreach(String szPart in dayParts)
            {
                int num = Convert.ToInt16(szPart);
                szDay2 += (num >999 ? num.ToString().Substring(2):num < 10 ? "0" + num.ToString(): num.ToString());
;
            }

            return szDay2;
        }
        static void Main(string[] args)
        {

          //  ClassMovieMaker test= new ClassMovieMaker();
           //     String line6 = "PR_LEAP_AM_1819_6,15:24.4,1.566782,4.620952,269.4004,FALSE,Typical,M,Child,1.126675,4.625558,2.00689,4.616347,FALSE,0,0";
             //          line6 = "PR_LEAP_AM_1819_6,15:24.4,1.566782,4.620952,269.4004,FALSE,Typical,M,Child,1,4,2,3,FALSE,0,0";

              //  test.getTrianglePoints(line6.Split(','), 0.5);
            //  test.getTrianglePoints2(line6.Split(','), 0.5);
            //10THOFSECTALKING_1_23_2019_9_9_2019_2019566646



            String dataDir = "E://CLASSROOMS_AS_OF_FEB2019//LADYBUGS1//SYNC//";//"E://MOVIES//"
            String movieDIr = "E://MOVIES//";
            string days = "11_1_2019,12_9_2019,1_30_2020,2_28_2020,3_9_2020";
            String fileVersion = "_5_25_2019_237784429";
            int movieCount = 0;


            //F:\StarFish_2021\SYNC\COTALK\DAYCOTALK_031621_GR0_22_040821_1117659851.CSV
            /******STARFISH2021*******/
            //DAYCOTALK_040621_GR0_22_5_062921_821889800
            dataDir = "E://StarFish_2021//SYNC//COTALK//";// "F://StarFish_2021//SYNC//";// COTALK//";//"E://MOVIES//"
            movieDIr = "E://MOVIES//";
            days = "4_6_2021"; 
            fileVersion = "_GR0_22_5_062921_821889800";// "_4_8_2021_778841436";// "_040821_1117659851";
            ClassMovieMaker msf21;
            foreach (String day in days.Split(','))
            {
                msf21 = new ClassMovieMaker(movieDIr, "SF21_" + day, dataDir + "DAYCOTALK_" + szDay(day) + fileVersion + ".CSV", 16, 16, true, "Typical", Color.Red, true);
                //msf21 = new ClassMovieMaker(movieDIr, "StarFish_2021_" + day, dataDir + "DAYCOTALK_031621_GR0_22_040821_2023709410.CSV", 15, 15, true, "", Color.Red, true);
                //ffmpeg -i "concat:input1.avi|input2.avi|input3.avi" -c copy output.avi
                //szMerge.Add("ffmpeg -i \"" + msf20.szfileNames + "\" -c copy " + msf20.szfileNames.Split('|')[0].Replace("_PART", ""));
            }
            /******STARFISH2021*******/


            /******TURTLES 1920******/
            dataDir = "G://CLASSROOMS1920//TURTLES_1920//SYNC//";//"E://MOVIES//"
            movieDIr = "E://MOVIES//";
            fileVersion = "_7_10_2020_1186946197";//_4_21_2020_1508344901
            days = "11_13_2019,12_6_2019"; //days = "12_6_2019,1_24_2020,2_12_2020,11_13_2019";//"11_13_2019,12_6_2019,1_24_2020";// "2_12_2020";
            ClassMovieMaker mpT;
            foreach (String day in days.Split(','))
            {
                mpT = new ClassMovieMaker(movieDIr, "TURTLES_" + day, dataDir + "10THOFSECTALKINGDETAIL_" + day + fileVersion + ".CSV", 12, 12, true, "Typical", Color.Red, true);
            }
            /******TURTLES 1920******/


            /******APPLETREE 1920******/
            dataDir = "G://CLASSROOMS1920//AppleTree_1920//SYNC//";//"E://MOVIES//"
            movieDIr = "E://MOVIES//";
            fileVersion = "_7_22_2020_1260238996";
            days = "3_10_2020,9_19_2019,10_1_2019,10_29_2019,11_5_2019,11_19_2019,12_10_2019,12_17_2019,1_8_2020,1_14_2020,2_4_2020,2_11_2020,3_10_2020"; //"11_1_2019";
            ClassMovieMaker mA1920;
            movieCount = 0;
            foreach (String day in days.Split(','))
            {
                mA1920 = new ClassMovieMaker(movieDIr, "APPLETREE_1920" + movieCount + "_" + day, dataDir + "10THOFSECTALKINGDETAIL_" + day + fileVersion + ".CSV", 9, 9, true, "TD", Color.Red, true);
                //new ClassMovieMaker(movieDIr, "PL1920AM_"+ day, dataDir + "10THOFSECTALKING_" + day+ fileVersion+".CSV", 9, 9, true, "", Color.Red, true);
            }
            /******APPLETREE 1920******/

            //_2_6_2020_5_20_2020_1113551224
            //7_16_2020_445802090
            List<String> szMerge = new List<string>();
            //\\datastore01.psy.miami.edu\Groups\LPerry_Lab\IBSS\Debbie_School\LadyBugs_Spring17\Synched_Data\COTALK\10THOFSECTALKING_5_12_2017_7_10_2019_1923851764


            /******PRIDE_LEAP AM 1920******/
            dataDir = "G://CLASSROOMS1920//LEAP_1920//LEAP_AM_1920//SYNC//";//"E://MOVIES//"
            movieDIr = "E://MOVIES//";
            fileVersion = "_7_7_2020_1207890104";
            days = "3_9_2020,11_1_2019"; //"11_1_2019";
            ClassMovieMaker mpl2;
            movieCount = 0;
            foreach (String day in days.Split(','))
            {
                //mpl2 = new ClassMovieMaker(movieDIr, "PL1920AM_" + movieCount + "_" + day, dataDir + "10THOFSECTALKINGDETAIL_" + day + fileVersion + ".CSV", 9, 9, true, "TD", Color.Red, true);
                //new ClassMovieMaker(movieDIr, "PL1920AM_"+ day, dataDir + "10THOFSECTALKING_" + day+ fileVersion+".CSV", 9, 9, true, "", Color.Red, true);
            }
            /******PRIDE_LEAP AM 1920******/
            /******PRIDE_LEAP PM 1920******/
            dataDir = "G://CLASSROOMS1920//LEAP_1920//LEAP_PM_1920//SYNC//";//"E://MOVIES//"
            movieDIr = "E://MOVIES//";
            fileVersion = "_7_7_2020_1019028736";//"_7_7_2020_1019028736";
            days = "11_1_2019,12_9_2019,1_30_2020,2_28_2020,3_9_2020,11_1_2019"; //"11_1_2019,2_28_2020,3_9_2020";// "11_1_2019,12_9_2019,1_30_2020,2_28_2020,3_9_2020,11_1_2019";
            days = "1_30_2020,2_28_2020"; //"11_1_2019,2_28_2020,3_9_2020";// "11_1_2019,12_9_2019,1_30_2020,2_28_2020,3_9_2020,11_1_2019";
            ClassMovieMaker mp1920;
              movieCount = 0;
            foreach (String day in days.Split(','))
            {
                
                mp1920 = new ClassMovieMaker(movieDIr, "PL1920PM_" + movieCount + "_" + day, dataDir + "10THOFSECTALKINGDETAIL_" + day + fileVersion + ".CSV", 9, 9, true, "TD", Color.Red, true);
            }
            /******PRIDE_LEAP PM 1920******/


            /******STARFISH1920*******/
            //3/3/2017,3/10/2017,3/17/2017,3/31/2017,4/7/2017,4/21/2017,4/28/2017,5/12/2017,5/19/2017,5/26/2017
            dataDir = "G://CLASSROOMS1920//StarFish_1920//SYNC//";//"E://MOVIES//"
            movieDIr = "D://MOVIES//";
            days = "10_2_2019,11_26_2019,12_2_2019,1_28_2020,2_24_2020,10_2_2019";

            fileVersion = "_7_16_2020_445802090";
            ClassMovieMaker msf20;
            foreach (String day in days.Split(','))
            {
                msf20 = new ClassMovieMaker(movieDIr, "StarFish_1920_" + day, dataDir + "10THOFSECTALKINGDETAIL_" + day + fileVersion + ".CSV", 15, 15, true, "Typical", Color.Red, true);
                //ffmpeg -i "concat:input1.avi|input2.avi|input3.avi" -c copy output.avi
                //szMerge.Add("ffmpeg -i \"" + msf20.szfileNames + "\" -c copy " + msf20.szfileNames.Split('|')[0].Replace("_PART", ""));
            }
            /******STARFISH1920*******/
            foreach (String code in szMerge)
            {
               // Console.WriteLine(code);
            }

            //ffmpeg -i "concat:input1.avi|input2.avi|input3.avi" -c copy output.avi

            /******PANDAS1920*******/
            //3/3/2017,3/10/2017,3/17/2017,3/31/2017,4/7/2017,4/21/2017,4/28/2017,5/12/2017,5/19/2017,5/26/2017
            dataDir = "G://CLASSROOMS1920//Pandas_1920//SYNC//";//"E://MOVIES//"
            movieDIr = "D://MOVIES//";
            days = "9_17_2019,9_24_2019,10_24_2019,10_30_2019,11_20_2019,12_18_2019,12_18_2019,12_19_2019,1_9_2020,1_13_2020,2_3_2020,2_6_2020,3_3_2020,9_17_2019";

            fileVersion = "_5_20_2020_1113551224";
            ClassMovieMaker mp20;
            foreach (String day in days.Split(','))
            {
                mp20 = new ClassMovieMaker(movieDIr, "PANDAS1920_" + day, dataDir + "10THOFSECTALKING_" + day + fileVersion + ".CSV", 13, 13, true, "Typical", Color.Red, true);
                szMerge.Add("ffmpeg -i \"" + mp20.szfileNames + "\" -c copy output.avi" + mp20.szfileNames.Split('|')[0].Replace("PART", ""));
            }
            /******PANDAS1920*******/




            /******LB1*******/
            //3/3/2017,3/10/2017,3/17/2017,3/31/2017,4/7/2017,4/21/2017,4/28/2017,5/12/2017,5/19/2017,5/26/2017
 




            dataDir = "\\\\datastore01.psy.miami.edu\\Groups\\LPerry_Lab\\IBSS\\Debbie_School\\LadyBugs_Spring17\\Synched_Data\\COTALK\\";//"G://CLASSROOMS_OLD//LB17//SYNC//";//"E://MOVIES//"
            movieDIr = "D://MOVIES//";
            days = "3_3_2017,3_10_2017,3_17_2017,3_31_2017,4_7_2017,4_21_2017,4_28_2017,5_12_2017,5_19_2017,5_26_2017,3_3_2017";
            days = "5_26_2017,5_19_2017";
            days = "3_3_2017,3_10_2017,3_17_2017,3_31_2017,4_7_2017,4_21_2017,4_28_2017,5_12_2017,5_19_2017,5_26_2017";
            fileVersion = "_7_10_2019_1923851764";//"_7_10_2019_1923851764";
            ClassMovieMaker mlb1;
            foreach (String day in days.Split(','))
            {
                //mlb1 = new ClassMovieMaker(movieDIr, "LB1_2017_" + day, dataDir + "10THOFSECTALKING_" + day + fileVersion + ".CSV", 9, 9, true, "", Color.Red, true);
            }
            /******LB1*******/


            /****PRIDE_LEAP  * *****/
            /******PRIDE_LEAP AM******/
            // //10THOFSECTALKING_1_23_2019_9_9_2019_2019566646
            //10THOFSECTALKING_5_30_2019_6_29_2019_2028070651
            dataDir = "\\\\datastore01.psy.miami.edu\\Groups\\LPerry_Lab\\IBSS\\PRIDE\\PRIDE_LEAP_1819\\PRIDE_LEAP_AM\\SYNC\\COTALK\\";// "G://CLASSROOMS_OLD//PRIDE_LEAP//PRIDE_LEAP_AM//SYNC//";//"E://MOVIES//"
            movieDIr = "G://CLASSROOMS_OLD//PRIDE_LEAP//PRIDE_LEAP_AM//SYNC//MOVIES//";
            days = "1_23_2019,2_20_2019,3_20_2019,4_16_2019,5_30_2019";
            days = "5_30_2019,1_23_2019";

            fileVersion = "_5_19_2020_2019412578";// "_9_9_2019_2019566646";//"_6_29_2019_2028070651";
            ClassMovieMaker mpl1;
            foreach (String day in days.Split(','))
            {
                mpl1 = new ClassMovieMaker(movieDIr, "PL1819AM_"+ day, dataDir + "10THOFSECTALKING_" + day+ fileVersion+".CSV", 9, 9, true, "Typical", Color.Red, true);
            }

            /****PRIDE_LEAP  PM* *****/
            days = "1_25_2019,2_20_2019,3_20_2019,4_16_2019,5_30_2019,1_25_2019";
            days = "1_25_2019,2_20_2019";
            dataDir = "\\\\datastore01.psy.miami.edu\\Groups\\LPerry_Lab\\IBSS\\PRIDE\\PRIDE_LEAP_1819\\PRIDE_LEAP_PM\\SYNC\\COTALK\\";// "G://CLASSROOMS_OLD//PRIDE_LEAP//PRIDE_LEAP_AM//SYNC//";//"E://MOVIES//"
            fileVersion = "_7_7_2020_783683747";//

            foreach (String day in days.Split(','))
            {
                mpl1 = new ClassMovieMaker(movieDIr, "PL1819PM_" + day, dataDir + "10THOFSECTALKINGDETAIL_" + day + fileVersion + ".CSV", 9, 9, true, "Typical", Color.Red, true);
            }
            
            /******PRIDE_LEAP******/



          


            foreach(String code in szMerge)
            {
                Console.WriteLine(code);
            }
            

            

            /******PRIDE_LEAP TEST******/
            dataDir = "E://";//"E://MOVIES//"
            movieDIr = "E://MOVIES//";
            fileVersion = "_9_9_2019_2019566646";
            days = "1_23_2019";
            ClassMovieMaker mplT;
            foreach (String day in days.Split(','))
            {
                // mplT = new ClassMovieMaker(movieDIr, "PLTEST_"+ day, dataDir + "10THOFSECTALKING_" + day+ fileVersion+".CSV", 9, 9, true, "Typical", Color.Red, true);
            }
            /******PRIDE_LEAP TEST******/
            ///TEST 10THOFSECTALKING_1_23_2019_9_9_2019_2019566646


            

           


            /******PRIDE_REVM******/
            //10THOFSECTALKING_5_28_2019_6_30_2019_348275411
            dataDir = "C://LVL//PRIDE_REVM//SYNC//";//"E://MOVIES//"
            movieDIr = "E://MOVIES//";
            days = "3_1_2019,3_19_2019,4_24_2019,5_28_2019";
            days = "4_24_2019,5_28_2019";
            fileVersion = "_6_30_2019_348275411";
            ClassMovieMaker mpr1;
            foreach (String day in days.Split(','))
            {
                mpr1 = new ClassMovieMaker(movieDIr, "PR1_" + day, dataDir + "10THOFSECTALKING_" + day + fileVersion + ".CSV", 9, 9, true, "", Color.Red, true);
            }
            /******PRIDE_REVM******/


            /******PANDAS*******/
            dataDir = "E://CLASSROOMS_AS_OF_FEB2019//PANDAS//SYNC//";//"E://MOVIES//"
            movieDIr = "E://MOVIES//";
            days = "2_1_2018,2_8_2018,3_1_2018,4_6_2018,4_10_2018,5_3_2018,5_10_2018";
            fileVersion = "_6_5_2019_1317970681";
            ClassMovieMaker mp;
            foreach (String day in days.Split(','))
            {
              //  mp = new ClassMovieMaker(movieDIr, "PANDAS_" + day, dataDir + "10THOFSECTALKING_" + day + fileVersion + ".CSV", 16, 16, true, "", Color.Red, true);
            }
            /******PANDAS*******/
             
            /******LB2*******/
            //10/24/2017,11/3/2017,11/17/2017,12/14/2017,1/11/2018,2/2/2018,2/16/2018,3/13/2018,3/20/2018,5/1/2018,5/16/2018
            dataDir = "E://CLASSROOMS_AS_OF_FEB2019//LADYBUGS2//SYNC//";//"E://MOVIES//"
            movieDIr = "E://MOVIES//";
            days = "10_24_2017,11_3_2017,11_17_2017,12_14_2017,1_11_2018,2_2_2018,2_16_2018,3_13_2018,3_20_2018,5_1_2018,5_16_2018";
            fileVersion = "_5_24_2019_1820967679";
            ClassMovieMaker mlb2;
            foreach (String day in days.Split(','))
            {
              //  mlb2 = new ClassMovieMaker(movieDIr, "LB2_" + day, dataDir + "10THOFSECTALKING_" + day + fileVersion+ ".CSV", 9, 9, true, "", Color.Red, true);
            }
            /******LB2*******/

            //10THOFSECTALKING_5_14_2019_6_26_2019_2135690318
            /******LB3*******/
            //10/24/2017,11/3/2017,11/17/2017,12/14/2017,1/11/2018,2/2/2018,2/16/2018,3/13/2018,3/20/2018,5/1/2018,5/16/2018
            dataDir = "C://LVL//LADYBUGS_1819//SYNC//";//"E://MOVIES//"
            movieDIr = "E://MOVIES//";
            days = "4_2_2019,5_7_2019,5_14_2019,5_24_2019";
            fileVersion = "_6_26_2019_2135690318";
            ClassMovieMaker mlb3;
            foreach (String day in days.Split(','))
            {
                mlb3 = new ClassMovieMaker(movieDIr, "LB3_" + day, dataDir + "10THOFSECTALKING_" + day + fileVersion + ".CSV", 9, 9, true, "", Color.Red, true);
            }
            /******LB2*******/

            /*mlb2 = new ClassMovieMaker(movieDIr, "LB2_10_24_2017", dataDir+"10THOFSECTALKING_10_24_2017_5_24_2019_1820967679.CSV", 9, 9, true, "", Color.Red, true);
            mlb2 = new ClassMovieMaker(movieDIr, "LB2_11_3_2017", dataDir+"10THOFSECTALKING_11_3_2017_5_24_2019_1820967679.CSV", 9, 9, true, "", Color.Red, true);
            mlb2 = new ClassMovieMaker(movieDIr, "LB2_11_17_2017", dataDir+"10THOFSECTALKING_12_14_2017_5_24_2019_1820967679.CSV", 9, 9, true, "", Color.Red, true);
            mlb2 = new ClassMovieMaker(movieDIr, "LB2_12_14_2017", dataDir+"10THOFSECTALKING_11_3_2017_5_24_2019_1820967679.CSV", 9, 9, true, "", Color.Red, true);
            mlb2 = new ClassMovieMaker(movieDIr, "LB2_1_11_2018", dataDir+"10THOFSECTALKING_1_11_2018_5_24_2019_1820967679.CSV", 9, 9, true, "", Color.Red, true);
            mlb2 = new ClassMovieMaker(movieDIr, "LB2_2_2_2018", dataDir+"10THOFSECTALKING_2_2_2018_5_24_2019_1820967679.CSV", 9, 9, true, "", Color.Red, true);
            mlb2 = new ClassMovieMaker(movieDIr, "LB2_2_16_2018", dataDir+"10THOFSECTALKING_2_16_2018_5_24_2019_1820967679.CSV", 9, 9, true, "", Color.Red, true);
            mlb2 = new ClassMovieMaker(movieDIr, "LB2_3_13_2018", dataDir+"10THOFSECTALKING_3_13_2018_5_24_2019_1820967679.CSV", 9, 9, true, "", Color.Red, true);
            mlb2 = new ClassMovieMaker(movieDIr, "LB2_3_20_2018", dataDir+"10THOFSECTALKING_3_20_2018_5_24_2019_1820967679.CSV", 9, 9, true, "", Color.Red, true);
            mlb2 = new ClassMovieMaker(movieDIr, "LB2_5_1_2018", dataDir+"10THOFSECTALKING_5_1_2018_5_24_2019_1820967679.CSV", 9, 9, true, "", Color.Red, true);
            mlb2 = new ClassMovieMaker(movieDIr, "LB2_5_16_2018", dataDir+"10THOFSECTALKING_5_16_2018_5_24_2019_1820967679.CSV", 9, 9, true, "", Color.Red, true);
            */

        }
    }
}
