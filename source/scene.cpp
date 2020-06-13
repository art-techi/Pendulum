/* Set up scene with nodes and grid.
 * Create nodes, pass them to be rendered
 * and updated.
 */

#include "Scene.hpp"
#include <atlas/gl/GL.hpp>
#include <atlas/utils/GUI.hpp>

#include "Node.hpp"
#include <iostream>
#include "line.hpp"

namespace assignment2
{
    Scene::Scene() {
        //initialize variables
        mX=5;
        mL1=5;
        mTheta=glm::radians(45.0f);
        mY=-mL1*sin(mTheta);
        mL2=5;
        mK=0.5f;
        mGravity=-3.0f;
        mMass=1.0f;
        mYDot = -0.1f;

        //create 4 nodes for anchors, pulleys, and weightless node
        std::shared_ptr<Node> node1(new Node(atlas::math::Vector(0, 0, 0)));
        std::shared_ptr<Node> node2(new Node(atlas::math::Vector(mX, 0, 0)));
        std::shared_ptr<Node> node3(new Node(atlas::math::Vector(mX+mL1*cos(mTheta), mY, 0)));
        float x3 = node2->getPosition().x;
        std::shared_ptr<Node> node4(new Node(atlas::math::Vector(x3, mY-mL2, 0)));

        //draw a line between them (for better visual representation)
        std::shared_ptr<Line> line(new Line(node1, node2));
        std::shared_ptr<Line> line2(new Line(node2, node3));
        std::shared_ptr<Line> line3(new Line(node3, node4));

        //push nodes into node list
        mNodes.push_back(node1);
        mNodes.push_back(node2);
        mNodes.push_back(node3);
        mNodes.push_back(node4);
        //push line into line list
        mLines.push_back(line);
        mLines.push_back(line2);
        mLines.push_back(line3);
    }

    void Scene::renderScene(){
        atlas::utils::Gui::getInstance().newFrame();
        float col = 100.0f/255.0f;
        glClearColor(col, col, col, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mProjection=glm::perspective(glm::radians(mCamera.getCameraFOV()),
                                       (float) mWidth/mHeight, 1.0f, 1000.0f);

        mUniformMatrixBuffer.bindBuffer();
        mUniformMatrixBuffer.bufferSubData(0, sizeof(atlas::math::Matrix4),
                                           &mProjection[0][0]);
        mView=mCamera.getCameraMatrix();
        mUniformMatrixBuffer.bufferSubData(sizeof(atlas::math::Matrix4),
                                           sizeof(atlas::math::Matrix4), &mView[0][0]);
        mUniformMatrixBuffer.bindBufferBase(0);
        mUniformMatrixBuffer.unBindBuffer();

        if(mShowGrid){
            mGrid.renderGeometry(mProjection, mView);
        }

        //render nodes
        for (auto& node : mNodes) {
            node->renderGeometry(mProjection, mView);
        }

        //render lines
        for(auto& line : mLines){
            line->renderGeometry(mProjection, mView);
        }

        ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_FirstUseEver);
        ImGui::Begin("Global HUD");
        ImGui::Checkbox("Show grid", &mShowGrid);
        if(ImGui::Button("Reset Camera")){
            mCamera.resetCamera();
        }

        ImGui::Text("%.3f ms/frame", 1000.0f/ImGui::GetIO().Framerate);
        ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
        ImGui::End();

        ImGui::Render();
    }

    void Scene::updateScene(double time){
        ModellingScene::updateScene(time);

        //lagrange equation
        float yDotDot=mGravity-(mK/mMass)*mY*((1.0f/sqrt((1.0f-pow((mY/mL1),2.0f))))-1.0f);

        //find y
        mYDot+=mTime.deltaTime*yDotDot;
        mY += mTime.deltaTime*mYDot;

        //find x and theta from constraint equations
        mX=mL1*(1.0f-cos(mTheta));
        mTheta=asin(mY/mL1);

        //update position with x, y, and theta
        mNodes[1]->setPosition(atlas::math::Vector(mX, 0.0f, 0.0f));
        mNodes[2]->setPosition(atlas::math::Vector(mX + mL1 * cos(mTheta), mY, 0.0f));
        float x3 = mNodes[2]->getPosition().x;
        mNodes[3]->setPosition(atlas::math::Vector(x3, mY-mL2, 0.0f));
    }
}
