// An auto-generated user wrapper template for the service "radler"
package etb2.wrappers;

import java.io.BufferedReader;
import java.io.InputStreamReader;

public class radlerWRP extends radlerETBWRP {
  /**
   * This wrapper has 3 variable(s) defined in its superclass that serve as argument(s) of its corresponding service:
   *  arg1 - of type string
   *  arg2 - of type string
   *  arg3 - of type string
   */
  @Override
  public void run() {
    if (mode.equals("++-")) {
      /*
       * {arg1, arg2} - contain(s) non-NULL value(s) that can be considered as input(s) to the service.
       * {arg3} - the wrapper developer is required to assign output(s) of the service to the variable(s) (currently assigned null).
       */
      // do something
      try {
        String resCMD = runCMD0("/home/vagrant/radler/radler.sh --ws_dir /tmp/" + this.arg2 + "/src compile " + this.arg1 + ".radl --plant plant --ROS");
        if (resCMD == null) {
          this.arg3 = "compiled";
          this.addClaimPredicate();
        }
        else {
          this.validClaim = false;
          System.out.println("radler compile failed\n" + resCMD);
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
      Process pr = run.exec(cmd0);
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
