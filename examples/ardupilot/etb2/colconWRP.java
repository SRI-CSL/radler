// An auto-generated user wrapper template for the service "colcon"
package etb2.wrappers;

import java.io.BufferedReader;
import java.io.File;
import java.io.InputStreamReader;

public class colconWRP extends colconETBWRP {
  /**
   * This wrapper has 2 variable(s) defined in its superclass that serve as argument(s) of its corresponding service:
   *  arg1 - of type string
   *  arg2 - of type string
   */
  @Override
  public void run() {
    if (mode.equals("+-")) {
      /*
       * {arg1} - contain(s) non-NULL value(s) that can be considered as input(s) to the service.
       * {arg2} - the wrapper developer is required to assign output(s) of the service to the variable(s) (currently assigned null).
       */
      // do something
      try {
        String resCMD = runCMD0(this.arg1, "colcon build --cmake-args -DSECURITY=ON --no-warn-unused-cli --symlink-install"); 
        if (resCMD != null) {
          if (resCMD.contains("failed")) {
            this.validClaim = false;
            System.out.println("colcon build failed\n" + resCMD);
          }
          else {
            this.arg2 = "built";
            this.addClaimPredicate();
            System.out.println("colcon build succeeded\n" + resCMD);
          }
        }
        else {
          this.validClaim = false;
          System.out.println("colcon build failed due to unknown reason");
        }
      } catch (Exception ex) {
        ex.printStackTrace();
      }
    } else {
      this.validClaim = false;
      System.out.println("unrecognized mode for colcon");
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
    return "colconv000";
  }

  private String runCMD0(String ws, String cmd0) {
    Runtime run = Runtime.getRuntime();
    String resCMD = null;
    try {
      File ws_dir = new File("/tmp/" + ws);
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
