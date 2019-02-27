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
 
            ClassMovieMaker m = new ClassMovieMaker("D://MOVIES//","PREVAM_01_30_2019RLPART", "C://LVL//PRIDE_REVERSE//PRIDE_REVM_AM//SYNC//10THOFSECTALKING_1_30_2019_2_20_2019_383953003.CSV", 9, 9, true, "Atypical", true);
            // m = new ClassMovieMaker("D://MOVIES//","PLEAP_01_23_2019RLPART", "C://LVL//PRIDE_LEAP//SYNC//10THOFSECTALKING_1_23_2019_1_29_2019_1763280350.CSV", 9, 9, true, "Atypical", true);
            // m = new ClassMovieMaker("D://MOVIES//","PLEAP_01_25_2019RLPART", "C://LVL//PRIDE_LEAP//SYNC//10THOFSECTALKING_1_25_2019_1_29_2019_1763280350.CSV", 9, 9, true, "Atypical", true);



        }
    }
}
