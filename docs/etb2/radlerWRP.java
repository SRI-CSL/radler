// An auto-generated user wrapper template for the service "radler"
package etb2.wrappers;

import java.io.BufferedReader;
import java.io.File;
import java.nio.file.Files;
import java.nio.file.Path;
import java.io.IOException;
import java.io.InputStreamReader;

public class radlerWRP extends radlerETBWRP {
  /**
   * This wrapper has 4 variable(s) defined in its superclass that serve as argument(s) of its corresponding service:
   *  arg1 - of type string
   *  arg2 - of type string
   *  arg3 - of type string
   *  arg4 - of type string
   */
  @Override
  public void run() {
    if (mode.equals("+++-")) {
      /*
       * {arg1, arg2, arg3} - contain(s) non-NULL value(s) that can be considered as input(s) to the service.
       * {arg4} - the wrapper developer is required to assign output(s) of the service to the variable(s) (currently assigned null).
       */
      // do something
      try {
        if (this.arg3.equals("compile")) {
          String resCMD = runCMD0("./radler.sh --ws_dir /tmp/" + this.arg2 + "/src compile examples/ardupilot/" + this.arg1 + ".radl --plant plant --ROS");
          if (resCMD == null) {
            this.arg4 = "compiled";
            this.addClaimPredicate();
          }
          else {
            this.validClaim = false;
            System.out.println("radler compile failed\n" + resCMD);
          }
        }
        else if (this.arg3.equals("dump")) {
          String resCMD = runCMD0("./radler.sh dump -O /tmp/" + this.arg2 + "/src/" + this.arg1 + ".radlo --filter_pred logical " + this.arg1);
          if (resCMD != null) {
            Files.writeString(Path.of("/tmp/" + this.arg2 + "/" + this.arg1 + ".json"), resCMD);
            this.arg4 = "jsonized";
            this.addClaimPredicate();
          }
          else {
            this.validClaim = false;
            System.out.println("radler dump failed\n" + resCMD);
          }
        }
        else if (this.arg3.equals("plantdot")) {
          String resCMD = runCMD0("./radler.sh plantdot -O /tmp/" + this.arg2 + "/src/" + this.arg1 + ".radlo --plant " + this.arg1 + ".plant"); 
          if (resCMD != null) {
            String dotFN = "/tmp/" + this.arg2 + "/" + this.arg1 + ".dot";
            String pngFN = "/tmp/" + this.arg2 + "/" + this.arg1 + ".png";
            Files.writeString(Path.of(dotFN), resCMD);
            String resCMD1 = runCMD0("dot " + dotFN + " -Tpng -o " + pngFN);
            if (resCMD1 == null) {
              this.arg4 = "plantdotted";
              this.addClaimPredicate();
            }
            else {
              this.validClaim = false;
              System.out.println("dot failed\n" + resCMD);
            }
          }
          else {
            this.validClaim = false;
            System.out.println("radler plantdot failed\n" + resCMD);
          }
        }
        else {
          this.validClaim = false;
          System.out.println("unrecognized command for radler");
        }
      } catch (Exception ex) {
        ex.printStackTrace();
      }
    } else {
      this.validClaim = false;
      System.out.println("unrecognized mode for radler");
    }
  }

  /**
   * This method needs to execute the tool to grab and return version of the tool
   */
  @Override
  public String getToolVersion() {
    // String version
    // do something
    // return version
    return "radlerv000";
  }

  private String runCMD0(String cmd0) {
    Runtime run = Runtime.getRuntime();
    String resCMD = null;
    try {
      System.out.println("run command - " + cmd0);
      File ws_dir = new File(System.getenv("RADLER_HOME"));
      Process pr = run.exec(cmd0, null, ws_dir);
      pr.waitFor();
      BufferedReader stdInput = new BufferedReader(new InputStreamReader(pr.getInputStream()));
      String rline = null;

      while ((rline = stdInput.readLine()) != null) {
        if (resCMD == null) {
          resCMD = rline;
        } else {
          resCMD = resCMD + "\n" + rline;
        }
      }
    } catch (Exception ex) {
      ex.printStackTrace();
    }
    return resCMD;
  }
}
