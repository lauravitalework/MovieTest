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
        
        static void Main(string[] args)
        {

            String dataDir = "E://CLASSROOMS_AS_OF_FEB2019//LADYBUGS1//SYNC//";//"E://MOVIES//"
            String movieDIr = "E://MOVIES//";
            String days = "11_1_2019,12_9_2019,1_30_2020,2_28_2020,3_9_2020";
            String fileVersion = "_5_25_2019_237784429";

            /******PRIDE_LEAP 1920******/
            dataDir = "F://CLASSROOMS1920//LEAP_1920//SYNC//";//"E://MOVIES//"
            movieDIr = "F://MOVIES//";
            fileVersion = "_3_18_2020_1590632667";
            days = "11_1_2019";
            ClassMovieMaker mpl2;
            foreach (String day in days.Split(','))
            {
                mpl2 = new ClassMovieMaker(movieDIr, "PL22_"+ day, dataDir + "10THOFSECTALKING_" + day+ fileVersion+".CSV", 9, 9, true, "", Color.Red, true);
            }
            /******PRIDE_LEAP 1920******/



            /******PRIDE_LEAP******/
            //10THOFSECTALKING_5_30_2019_6_29_2019_2028070651
            dataDir = "C://LVL//PRIDE_LEAP//SYNC//";//"E://MOVIES//"
            movieDIr = "E://MOVIES//";
            days = "1_23_2019,1_25_2019,2_20_2019,3_20_2019,4_16_2019,5_30_2019";
            days = "5_30_2019";

            fileVersion = "_6_29_2019_2028070651";
            ClassMovieMaker mpl1;
            foreach (String day in days.Split(','))
            {
              //  mpl1 = new ClassMovieMaker(movieDIr, "PL1_"+ day, dataDir + "10THOFSECTALKING_" + day+ fileVersion+".CSV", 9, 9, true, "", Color.Red, true);
            }
            /******PRIDE_LEAP******/


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


            /******LB1*******/
            //3/3/2017,3/10/2017,3/17/2017,3/31/2017,4/7/2017,4/21/2017,4/28/2017,5/12/2017,5/19/2017,5/26/2017
            dataDir = "E://CLASSROOMS_AS_OF_FEB2019//LADYBUGS1//SYNC//";//"E://MOVIES//"
            movieDIr = "E://MOVIES//";
            days = "3_3_2017,3_10_2017,3_17_2017,3_31_2017,4_7_2017,4_21_2017,4_28_2017,5_12_2017,5_19_2017,5_26_2017";
            fileVersion = "_5_25_2019_237784429";
            ClassMovieMaker mlb1;
            foreach(String day in days.Split(','))
            {
               // mlb1 = new ClassMovieMaker(movieDIr, "LB1_"+ day, dataDir + "10THOFSECTALKING_" + day+ fileVersion+".CSV", 9, 9, true, "", Color.Red, true);
            }
            /******LB1*******/

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
