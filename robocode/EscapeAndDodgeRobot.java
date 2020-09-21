package EscapeAndDodge;
import robocode.*;
import java.awt.Color;
import robocode.util.*;
import java.awt.geom.*;

/**
 * @author ??????^
 * @version 1.0
 */

public class EscapeAndDodgeRobot extends AdvancedRobot
{
  double fx, fy, cx, cy;
  double sx, sy;
  int Enemy;
  int i;
  int j = 0;
  int dir = 1;
  double EnemyEnergy = 100;
  String mode = "Escape";

  static double oldEnemyHeading;

  /**
   *???C?????\?b?h???
   */
  public void run() {
    setAdjustRadarForRobotTurn(true);
    setAdjustGunForRobotTurn(true);
    setAdjustRadarForGunTurn(true);

    setTurnRadarRight(1000);
    execute();
    Enemy = getOthers();
    if(Enemy <= 1){
      mode = "Dodge";
    }

    SetFieldData();
    if(mode.equals("Escape")){
      MoveCorner();
    }

    while(true) {
      Enemy = getOthers();
      if(Enemy <= 1){
        mode = "Dodge";
      }
      if (getRadarTurnRemaining() == 0){
        setTurnRadarRight(360);
      }
      if(mode.equals("Escape")){
        EscapeMode();
      }
      execute();
    }
  }

    /**
   *?t?B?[???h??????E???{?b?g??o???n?_?E???{?b?g??J???[???Z?b?g???ˆè?\?b?h???
   */
  public void SetFieldData(){

    fx = getBattleFieldWidth();
    fy = getBattleFieldHeight();
    cx = getBattleFieldWidth() / 2;
    cy = getBattleFieldHeight() / 2;
    sx = getX();
    sy = getY();
    setColors(Color.green, Color.black, Color.gray);
  }

  /**
   * ???????????????ˆè?\?b?h????B
   * ?G??2???ƒA?????X?^?[?g??????????s???????B
   */

  public void MoveCorner(){
    if(fx / 2 >= sx && fy / 2 <= sy){
      turnRight(-getHeading() + 90);
      ahead(fx - sx - 75);
      i = 1;
    }
    else if(fx / 2 < sx && fy / 2 <= sy){
      turnRight(-getHeading() - 180);
      ahead(sy - 75);
      i = 2;
    }
    else if(fx / 2 >= sx && fy / 2 > sy){
      turnRight(-getHeading());
      ahead(fy - sy - 75);
      i = 0;
    }
    else if(fx / 2 < sx && fy / 2 > sy){
      turnRight(-getHeading() - 90);
      ahead(sx - 75);
      i = 3;
    }
    execute();
  }
 /**
  * ?G??2??????????s????ˆè?\?b?h????B
  * ??????\?b?h???O????????s??????B
  */
  public void EscapeMode(){
    if(i == 0){
      if(fy - 150 <= getY()){
        setTurnRight(90);
        i++;
      }
    }
    else if(i == 1){
      if(fx - 150 <= getX()){
        setTurnRight(90);
        i++;
      }
    }
    else if(i == 2){
      if(fy - 850 >= getY()){
        setTurnRight(90);
        i++;
      }
    }
    else if(i == 3){
      if(fx - 850 >= getX()){
        setTurnRight(90);
        i = 0;
      }
    }
    setAhead(10000);
  }

/**
 * ???[?_?[??G???????????s????ˆè?\?b?h????B
 * ?\????G??1????????????s??????B
 * @param e ???[?_?[??????????{?b?g????i?[??????????B
 */
  public void onScannedRobot(ScannedRobotEvent e) {
    double myX = getX();
    double myY = getY();
    double absoluteBearing = getHeadingRadians() + e.getBearingRadians();
    double enemyX = getX() + e.getDistance() * Math.sin(absoluteBearing);
    double enemyY = getY() + e.getDistance() * Math.cos(absoluteBearing);
    double enemyHeading = e.getHeadingRadians();
    double enemyHeadingChange = enemyHeading - oldEnemyHeading;
    double enemyVelocity = e.getVelocity();
    oldEnemyHeading = enemyHeading;

    double deltaTime = 0;
    double battleFieldHeight = getBattleFieldHeight();
    double battleFieldWidth = getBattleFieldWidth();
    double predictedX = enemyX;
    double predictedY = enemyY;
    double Energy = EnemyEnergy - e.getEnergy();


    while((++deltaTime) * (20.0 - 3.0 * 1) < Point2D.Double.distance(myX, myY, predictedX, predictedY)){
      predictedX += Math.sin(enemyHeading) * enemyVelocity;
      predictedY += Math.cos(enemyHeading) * enemyVelocity;

      enemyHeading += enemyHeadingChange;
      if(	predictedX < 18.0|| predictedY < 18.0|| predictedX > battleFieldWidth - 18.0|| predictedY > battleFieldHeight - 18.0){
        predictedX = Math.min(Math.max(18.0, predictedX), battleFieldWidth - 18.0);
        predictedY = Math.min(Math.max(18.0, predictedY), battleFieldHeight - 18.0);
        break;
      }
    }
    double theta = Utils.normalAbsoluteAngle(Math.atan2(predictedX - getX(), predictedY - getY()));
    setTurnRadarRightRadians(Utils.normalRelativeAngle(absoluteBearing - getRadarHeadingRadians()));
    setTurnGunRightRadians(Utils.normalRelativeAngle(theta - getGunHeadingRadians()));

    if(mode.equals("Dodge")){
      if(Energy > 0 && Energy <= 3){
        EnemyEnergy = e.getEnergy();
        if(e.getDistance() < 300){
          setTurnRight(e.getBearing() + 45);
          setBack(60 * dir);
        }
        else if(e.getDistance() > 900){
          setTurnRight(e.getBearing() + 45);
          setAhead(50 * dir);
        }
        else{
          setTurnRight(e.getBearing() + 90);
          setAhead(50 * dir);
        }
      }
    }
    j++;
    if(j >= 2){
      fire(1.0);
      j = 0;
    }

    EnemyEnergy = e.getEnergy();

    }
/**
 * ?????{?b?g???????????????????ˆè?\?b?h????B
 * @param e ?????????{?b?g????i?[??????????B
 */
    public void onHitWall(HitWallEvent e) {
      dir *= -1;
      setTurnRight(-90);
      setAhead(100);
    }

/**
 * ??????{?b?g?????????????s?????ˆè?\?b?h????B
 * @param e ?????????{?b?g????i?[??????????B
 */
    public void onHitRobot(HitRobotEvent e){
      j++;
    if(j >= 2){
      fire(3.0);
      j = 0;
    }
      dir *= -1;
    }
  }
