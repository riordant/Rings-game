
//Some Windows Headers (For Time, IO, etc.)
//#include <windows.h>
//#include <mmsystem.h>
#include "maths_funcs.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "camera.cpp"
#include <pthread.h>
#include <iostream>
#include <GL/glew.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "text.h"
#include <chrono>

// Assimp includes
#include <assimp/assimp-3.1.1/include/assimp/cimport.h> // C importer
#include <assimp/assimp-3.1.1/include/assimp/scene.h> // collects data
#include <assimp/assimp-3.1.1/include/assimp/postprocess.h> // various extra operations
#include <stdio.h>
#include <vector> // STL dynamic memory.

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtx/transform.hpp>

#include <irrKlang.h>
#include "conio.h"

using namespace irrklang;
using namespace std;

int score;
unsigned long GAME_LENGTH_SECONDS = 30;
unsigned long beg_time = clock();

vector<const char *> sounds;

const int X = 0;
const int Y = 1;
const int Z = 2;

enum desert
{
    BALL_0 = 0,
    BALL_STAND_0 = 1,
    BOTTOM_SCENE = 2,
    OUTER_RIM = 3,
    SAND = 4,
    WATER = 5,
    RIM_END = 6,
    RIM_CONNECTOR = 7,
    PALM_TREE_0 = 8,
    TREE_CONNECTOR_0 = 9,
    PALM_TREE_1 = 10,
    TREE_CONNECTOR_1 = 11,
    PALM_TREE_2 = 12,
    TREE_CONNECTOR_2 = 13,
    PALM_TREE_3 = 14,
    TREE_CONNECTOR_3 = 15,
    PALM_TREE_4 = 16,
    TREE_CONNECTOR_4 = 17,
    BALL_1 = 18,
    BALL_STAND_1 = 19,
    BALL_2 = 20,
    BALL_STAND_2 = 21,
    BALL_3 = 22,
    BALL_STAND_3 = 23,
    BALL_4 = 24,
    BALL_STAND_4 = 25,
    BALL_5 = 26,
    BALL_STAND_5 = 27,
    BALL_6 = 28,
    BALL_STAND_6 = 29,
    BALL_7 = 30,
    BALL_STAND_7 = 31,
    BALL_8 = 32,
    BALL_STAND_8 = 33,
    BALL_9 = 34,
    BALL_STAND_9 = 35,
    BALL_10 = 36,
    BALL_STAND_10 = 37,
    BALL_11 = 38,
    BALL_STAND_11 = 39,
    BALL_12 = 40,
    BALL_STAND_12 = 41,
    BALL_13 = 42,
    BALL_STAND_13 = 43
};

enum rings
{
    RING_0 = 44,
    RING_1 = 45,
    RING_2 = 46,
    RING_3 = 47,
    RING_4 = 48,
    RING_5 = 49,
    RING_6 = 50,
    RING_7 = 51,
    RING_8 = 52,
    RING_9 = 53,
    RING_10 = 54,
    RING_11 = 55,
    RING_12 = 56
};

class timer
{
private:
    unsigned long begTime;
public:
    void start() {
        begTime = clock();
    }
    
    unsigned long elapsedTime() {
        return ((unsigned long) clock() - begTime) / CLOCKS_PER_SEC;
    }
    
    bool isTimeout(unsigned long seconds) {
        return seconds >= elapsedTime();
    }
};


timer t;

int d_count = 0;
vector<bool> valid_meshes;
vector<const char *> object_names;
vector<GLuint> textures;

vector<vec3> ring_translations;

vector<float> g_vp, g_vn, g_vt;

vector<vector<GLfloat>> mesh_vps;

bool first_iteration = true;

vector<vec3> ring_centroids;
//all points from centroid for every ring.
//each outer vector is a ring
//inner vector is the lines of points. theres no need to distinguish between lines.
vector<vector<vec3>> ring_points_from_centroids;
int g_point_count=0;

vector<unsigned int> vp_vbos;
vector<unsigned int> vn_vbos;
vector<unsigned int> vt_vbos;

//char * name = "/Users/tadhgriordan/Documents/OpenGL/Lab 5/include/rings edited.obj";
//FILO queue. last element is newest element.
vector<glm::vec3> last_cam_positions;
glm::vec3 last_cam_position;

GLuint* mesh_vaos = (GLuint *) malloc(sizeof(GLuint)*100);

const int NUM_RINGS = 30;

int NUM_MESHES;

mat4* models = (mat4 *) malloc(sizeof(mat4)*100);

unsigned int vp_vbo;
unsigned int vn_vbo;
unsigned int vt_vbo;

vector<int> mesh_point_counts;

Camera cam = Camera();

// Macro for indexing vertex buffer
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

GLuint shaderProgramID;
ISoundEngine * SoundEngine = createIrrKlangDevice();

int width = 800;
int height = 600;

GLuint loc1, loc2, loc3;

GLfloat rotate = 45.0f;

bool firstMouse = true;
GLfloat lastX =  width  / 2.0;
GLfloat lastY =  height / 2.0;

#pragma region GLM
mat4 convert_glm_mat4(glm::mat4 src)
{
    
    mat4 dArray;
    
    const float *pSource = (const float*)glm::value_ptr(src);
    for (int i = 0; i < 16; ++i)
    {
        cout << "psource[i]: " << i << pSource[i] << endl;
        dArray.m[i] = pSource[i];
        cout << "d array m[i]: " << i << dArray.m[i] << endl;
    }
    return dArray;
}
vec3 convert_glm_vec3(glm::vec3 src){
    
    vec3 dArray;
    dArray.v[X] = src.x;
    dArray.v[Y] = src.y;
    dArray.v[Z] = src.z;
    
    return dArray;
}
#pragma endregion GLM


#pragma region TEXTURE LOADING
GLuint texture_load(char * path)
{
    int textureWidth, textureHeight, n;
    unsigned char * img = stbi_load(path, &textureWidth, &textureHeight, &n, STBI_rgb);
    if (img == nullptr) std::cout << "unable to find: "<< path << std::endl;
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(img);
    std::cout << "Loaded: " << path << std::endl;
    return texture;
}
#pragma endregion TEXTURE LOADING


#pragma region MESH LOADING
void update_cam_positions()
{
    last_cam_position = cam.getPosition();
    /*
    if(last_cam_positions.size()<2) last_cam_positions.push_back(cam.getPosition());
    else
    {
        for(int i=0;i<last_cam_positions.size();i++)
        {
            last_cam_positions[i] = last_cam_positions[i+1];
        }
        last_cam_positions.push_back(cam.getPosition());
    }
     */
}

float roundfs(float f)
{
    
    return (roundf(f * 100))/100;
}

void find_collision(vector<float> mesh_vp,glm::vec3 position)
{
    
    for(int i=0;i<mesh_vp.size();i+=3){
        
        if((fabs(roundfs(mesh_vp[i])-roundfs(position.x)<=.001)) && (fabs(roundfs(mesh_vp[i+1])-roundfs(position.y)) <=.001) && (fabs(roundfs(mesh_vp[i+2])-roundfs(position.z))<=.001)){
            cam.Position = last_cam_position;
        }
    }
    
}

void translate_positions(int mesh_index, mat4 model)
{
    //translates the vector points.
    vector<float> points = mesh_vps[mesh_index];
    for(int i=0;i<points.size();i+=3)
    {
        //cout << "old points: " << points[i] << " " << points[i+1] << " " << points[i+2] << endl;
        
        vec3 old_position = vec3(points[i],points[i+1],points[i+2]);
        vec4 new_position = model * vec4(old_position,1.0);
        
        points[i] = new_position.v[0];
        points[i+1] = new_position.v[1];
        points[i+2] = new_position.v[2];
        
        //cout << "new points: " << new_position.v[0] << " " << new_position.v[1] << " " << new_position.v[2] << endl;
    }
    mesh_vps[mesh_index] = points;

}

void clear_globals()
{
    g_point_count=0;
    g_vp.clear();
    g_vn.clear();
    g_vt.clear();
    cout << "g vp size after clear: " << g_vp.size() << endl;
    cout << "g vn size after clear: " << g_vn.size() << endl;
    cout << "g vt size after clear: " << g_vt.size() << endl;
}

void load_texture_names()
{
    textures.push_back(texture_load("/Users/tadhgriordan/Documents/OpenGL/Lab 5/include/images/ball.png")); // ball
    textures.push_back(texture_load("/Users/tadhgriordan/Documents/OpenGL/Lab 5/include/images/ball.png")); // ball stand
    textures.push_back(texture_load("/Users/tadhgriordan/Documents/OpenGL/Lab 5/include/images/sand.jpg")); // bottom of scene
    textures.push_back(texture_load("/Users/tadhgriordan/Documents/OpenGL/Lab 5/include/images/pink.jpg")); // outer rim
    textures.push_back(texture_load("/Users/tadhgriordan/Documents/OpenGL/Lab 5/include/images/sand.jpg")); // sand
    textures.push_back(texture_load("/Users/tadhgriordan/Documents/OpenGL/Lab 5/include/images/water.jpg"));// water
    textures.push_back(texture_load("/Users/tadhgriordan/Documents/OpenGL/Lab 5/include/images/pink.jpg"));// end of rim
    textures.push_back(texture_load("/Users/tadhgriordan/Documents/OpenGL/Lab 5/include/images/pink.jpg"));// rim connector
    textures.push_back(texture_load("/Users/tadhgriordan/Documents/OpenGL/Lab 5/include/images/tree.jpg"));// palm tree
    textures.push_back(texture_load("/Users/tadhgriordan/Documents/OpenGL/Lab 5/include/images/tree-dark.jpg"));// palm tree connector
    textures.push_back(texture_load("/Users/tadhgriordan/Documents/OpenGL/Lab 5/include/images/tree.jpg"));// palm tree
    textures.push_back(texture_load("/Users/tadhgriordan/Documents/OpenGL/Lab 5/include/images/tree-dark.jpg"));// palm tree connector
    textures.push_back(texture_load("/Users/tadhgriordan/Documents/OpenGL/Lab 5/include/images/tree.jpg"));// palm tree
    textures.push_back(texture_load("/Users/tadhgriordan/Documents/OpenGL/Lab 5/include/images/tree-dark.jpg"));// palm tree connector
    textures.push_back(texture_load("/Users/tadhgriordan/Documents/OpenGL/Lab 5/include/images/tree.jpg"));// palm tree
    textures.push_back(texture_load("/Users/tadhgriordan/Documents/OpenGL/Lab 5/include/images/tree-dark.jpg"));// palm tree connector
    textures.push_back(texture_load("/Users/tadhgriordan/Documents/OpenGL/Lab 5/include/images/tree.jpg"));// palm tree
    textures.push_back(texture_load("/Users/tadhgriordan/Documents/OpenGL/Lab 5/include/images/tree-dark.jpg"));// palm tree connector
    textures.push_back(texture_load("/Users/tadhgriordan/Documents/OpenGL/Lab 5/include/images/ball.png")); // ball
    textures.push_back(texture_load("/Users/tadhgriordan/Documents/OpenGL/Lab 5/include/images/ball.png")); // ball stand
    textures.push_back(texture_load("/Users/tadhgriordan/Documents/OpenGL/Lab 5/include/images/ball.png")); // ball
    textures.push_back(texture_load("/Users/tadhgriordan/Documents/OpenGL/Lab 5/include/images/ball.png")); // ball stand
    textures.push_back(texture_load("/Users/tadhgriordan/Documents/OpenGL/Lab 5/include/images/ball.png")); // ball
    textures.push_back(texture_load("/Users/tadhgriordan/Documents/OpenGL/Lab 5/include/images/ball.png")); // ball stand
    textures.push_back(texture_load("/Users/tadhgriordan/Documents/OpenGL/Lab 5/include/images/ball.png")); // ball
    textures.push_back(texture_load("/Users/tadhgriordan/Documents/OpenGL/Lab 5/include/images/ball.png")); // ball stand
    textures.push_back(texture_load("/Users/tadhgriordan/Documents/OpenGL/Lab 5/include/images/ball.png")); // ball
    textures.push_back(texture_load("/Users/tadhgriordan/Documents/OpenGL/Lab 5/include/images/ball.png")); // ball stand
    textures.push_back(texture_load("/Users/tadhgriordan/Documents/OpenGL/Lab 5/include/images/ball.png")); // ball
    textures.push_back(texture_load("/Users/tadhgriordan/Documents/OpenGL/Lab 5/include/images/ball.png")); // ball stand
    textures.push_back(texture_load("/Users/tadhgriordan/Documents/OpenGL/Lab 5/include/images/ball.png")); // ball
    textures.push_back(texture_load("/Users/tadhgriordan/Documents/OpenGL/Lab 5/include/images/ball.png")); // ball stand
    textures.push_back(texture_load("/Users/tadhgriordan/Documents/OpenGL/Lab 5/include/images/ball.png")); // ball
    textures.push_back(texture_load("/Users/tadhgriordan/Documents/OpenGL/Lab 5/include/images/ball.png")); // ball stand
    textures.push_back(texture_load("/Users/tadhgriordan/Documents/OpenGL/Lab 5/include/images/ball.png")); // ball
    textures.push_back(texture_load("/Users/tadhgriordan/Documents/OpenGL/Lab 5/include/images/ball.png")); // ball stand
    textures.push_back(texture_load("/Users/tadhgriordan/Documents/OpenGL/Lab 5/include/images/ball.png")); // ball
    textures.push_back(texture_load("/Users/tadhgriordan/Documents/OpenGL/Lab 5/include/images/ball.png")); // ball stand
    textures.push_back(texture_load("/Users/tadhgriordan/Documents/OpenGL/Lab 5/include/images/ball.png")); // ball
    textures.push_back(texture_load("/Users/tadhgriordan/Documents/OpenGL/Lab 5/include/images/ball.png")); // ball stand
    textures.push_back(texture_load("/Users/tadhgriordan/Documents/OpenGL/Lab 5/include/images/ball.png")); // ball
    textures.push_back(texture_load("/Users/tadhgriordan/Documents/OpenGL/Lab 5/include/images/ball.png")); // ball stand
    textures.push_back(texture_load("/Users/tadhgriordan/Documents/OpenGL/Lab 5/include/images/ball.png")); // ball
    textures.push_back(texture_load("/Users/tadhgriordan/Documents/OpenGL/Lab 5/include/images/ball.png")); // ball stand
    //textures.push_back(textureLoading("/Users/tadhgriordan/Documents/OpenGL/Lab 5/include/images/ring.jpg")); // ball
    //textures.push_back(textureLoading("/Users/tadhgriordan/Documents/OpenGL/Lab 5/include/images/ring.jpg")); // ball stand
    
    for(int i=0;i<NUM_RINGS;i++){
        textures.push_back(texture_load("/Users/tadhgriordan/Documents/OpenGL/Lab 5/include/images/ring.jpg")); // ring
    }
    
    cout << "textures size: " << textures.size() << endl;
}

void load_ring_translations()
{
    srand (time(0));
    for(int i=0;i<NUM_RINGS;i++)
    {

            int x = rand() % 17 + (-8);
            int y = rand() % 8 + 1;
            int z = rand() % 17 + (-8);
            ring_translations.push_back(vec3(x,y,z));
    }
}

void load_object_names()
{
    
    object_names.push_back("/Users/tadhgriordan/Documents/OpenGL/Lab 5/include/desert.obj");
    for(int i=0;i<NUM_RINGS;i++)
    {
        object_names.push_back("/Users/tadhgriordan/Documents/OpenGL/Lab 5/include/rings textured.obj");
    }
}

const aiScene* load_object(const char* file_name)
{
    cout << "file name: " << file_name << endl;
    const aiScene* scene = aiImportFile (file_name, aiProcess_Triangulate); // TRIANGLES!
    if (!scene)
    {
        fprintf (stderr, "ERROR: reading mesh %s\n", file_name);
    }
    
    printf ("  %i animations\n", scene->mNumAnimations);
    printf ("  %i cameras\n", scene->mNumCameras);
    printf ("  %i lights\n", scene->mNumLights);
    printf ("  %i materials\n", scene->mNumMaterials);
    printf ("  %i meshes\n", scene->mNumMeshes);
    printf ("  %i textures\n", scene->mNumTextures);
    
    
    return scene;
}

bool load_mesh(const aiScene* scene, int mesh_i)
{
        cout << "mesh_i LM: " << mesh_i << endl;
        const aiMesh* mesh = scene->mMeshes[mesh_i];
        printf ("%i vertices in mesh\n", mesh->mNumVertices);
        g_point_count = mesh->mNumVertices;
        
        for (unsigned int v_i = 0; v_i < mesh->mNumVertices; v_i++)
        {
            if (mesh->HasPositions ()) {
                const aiVector3D* vp = &(mesh->mVertices[v_i]);
                if(NUM_MESHES >= 44)
                { //scale rings by a half.
                    //printf ("      vp %i (%f,%f,%f)\n", v_i, vp->x, vp->y, vp->z);
                    mat4 scaler = scale(identity_mat4(),vec3(0.5,0.5,0.5));
                    vec3 old_position = vec3(vp->x,vp->y,vp->z);
                    vec4 new_position = scaler * vec4(old_position,1.0);
                    g_vp.push_back (new_position.v[0]);
                    g_vp.push_back (new_position.v[1]);
                    g_vp.push_back (new_position.v[2]);
                }
                else
                {
                    g_vp.push_back (vp->x);
                    g_vp.push_back (vp->y);
                    g_vp.push_back (vp->z);
                }
            }
            if (mesh->HasNormals ()) {
                const aiVector3D* vn = &(mesh->mNormals[v_i]);
                if(NUM_MESHES >= 44)
                { //scale rings by a half.
                    mat4 scaler = scale(identity_mat4(),vec3(0.5,0.5,0.5));
                    vec3 old_position = vec3(vn->x,vn->y,vn->z);
                    vec4 new_position = scaler * vec4(old_position,1.0);
                    g_vn.push_back (new_position.v[0]);
                    g_vn.push_back (new_position.v[1]);
                    g_vn.push_back (new_position.v[2]);
                }
                else
                {
                    g_vn.push_back (vn->x);
                    g_vn.push_back (vn->y);
                    g_vn.push_back (vn->z);
                }
            }
            if (mesh->HasTextureCoords (0)) {
                const aiVector3D* vt = &(mesh->mTextureCoords[0][v_i]);
                //printf ("      vt %i (%f,%f)\n", v_i, vt->x, vt->y);
                g_vt.push_back (vt->x);
                g_vt.push_back (vt->y);
            }
            if (mesh->HasTangentsAndBitangents ()) {
                // NB: could store/print tangents here
            }
        }
    return true;
}

#pragma endregion MESH LOADING



#pragma region SHADER_FUNCTIONS
// Create a NULL-terminated string by reading the provided file
char* readShaderSource(const char* shaderFile)
{
    FILE* fp = fopen(shaderFile, "rb"); //!->Why does binary flag "RB" work and not "R"... wierd msvc thing?

    if ( fp == NULL ) { return NULL; }

    fseek(fp, 0L, SEEK_END);
    long size = ftell(fp);

    fseek(fp, 0L, SEEK_SET);
    char* buf = new char[size + 1];
    fread(buf, 1, size, fp);
    buf[size] = '\0';

    fclose(fp);

    return buf;
}
static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
	// create a shader object
    GLuint ShaderObj = glCreateShader(ShaderType);

    if (ShaderObj == 0) {
        fprintf(stderr, "Error creating shader type %d\n", ShaderType);
        exit(0);
    }
	const char* pShaderSource = readShaderSource( pShaderText);

	// Bind the source code to the shader, this happens before compilation
	glShaderSource(ShaderObj, 1, (const GLchar**)&pShaderSource, NULL);
	// compile the shader and check for errors
    glCompileShader(ShaderObj);
    GLint success;
	// check for shader related errors using glGetShaderiv
    glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
        fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
        exit(1);
    }
	// Attach the compiled shader object to the program object
    glAttachShader(ShaderProgram, ShaderObj);
}
GLuint CompileShaders()
{
	//Start the process of setting up our shaders by creating a program ID
	//Note: we will link all the shaders together into this ID
    shaderProgramID = glCreateProgram();
    if (shaderProgramID == 0) {
        fprintf(stderr, "Error creating shader program\n");
        exit(1);
    }

	// Create two shader objects, one for the vertex, and one for the fragment shader
    AddShader(shaderProgramID, "/Users/tadhgriordan/Documents/Course/4th Year/Graphics/Assignments/OpenGL/Lab 5/Shaders/simpleVertexShader4.txt", GL_VERTEX_SHADER);
    AddShader(shaderProgramID, "/Users/tadhgriordan/Documents/Course/4th Year/Graphics/Assignments/OpenGL/Lab 5/Shaders/simpleFragmentShader4.txt", GL_FRAGMENT_SHADER);

    GLint Success = 0;
    GLchar ErrorLog[1024] = { 0 };
	// After compiling all shader objects and attaching them to the program, we can finally link it
    glLinkProgram(shaderProgramID);
	// check for program related errors using glGetProgramiv
    glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &Success);
	if (Success == 0) {
		glGetProgramInfoLog(shaderProgramID, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
        exit(1);
	}

	// program has been successfully linked but needs to be validated to check whether the program can execute given the current pipeline state
    glValidateProgram(shaderProgramID);
	// check for program related errors using glGetProgramiv
    glGetProgramiv(shaderProgramID, GL_VALIDATE_STATUS, &Success);
    if (!Success) {
        glGetProgramInfoLog(shaderProgramID, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
        exit(1);
    }
	// Finally, use the linked shader program
	// Note: this program will stay in effect for all draw calls until you replace it with another or explicitly disable its use
    glUseProgram(shaderProgramID);
	return shaderProgramID;
}
#pragma endregion SHADER_FUNCTIONS



#pragma region VBO_FUNCTIONS
void generateObjectBufferMesh(const aiScene* scene, int index, unsigned int vao)
{
/*----------------------------------------------------------------------------
                   LOAD MESH HERE AND COPY INTO BUFFERS
  ----------------------------------------------------------------------------*/

	//Note: you may get an error "vector subscript out of range" if you are using this code for a mesh that doesnt have positions and normals
	//Might be an idea to do a check for that before generating and binding the buffer.
    cout << "j GOBM:" << index << endl;
	load_mesh(scene,index);
    
	loc1 = glGetAttribLocation(shaderProgramID, "vertex_position");
	loc2 = glGetAttribLocation(shaderProgramID, "vertex_normal");
	loc3 = glGetAttribLocation(shaderProgramID, "vertex_texture");

    vp_vbos.push_back(vao);

	glGenBuffers (1, &vp_vbos.back());
	glBindBuffer (GL_ARRAY_BUFFER, vp_vbos.back());
    glBufferData (GL_ARRAY_BUFFER, g_point_count * 3 * sizeof (float), &g_vp[0], GL_STATIC_DRAW);
    
    vn_vbos.push_back(vao);
	glGenBuffers (1, &vn_vbos.back());
    glBindBuffer (GL_ARRAY_BUFFER, vn_vbos.back());
	glBufferData (GL_ARRAY_BUFFER, g_point_count * 3 * sizeof (float), &g_vn[0], GL_STATIC_DRAW);

    vt_vbos.push_back(vao);
    glGenBuffers (1, &vt_vbos.back());
    glBindBuffer (GL_ARRAY_BUFFER, vt_vbos.back());
	glBufferData (GL_ARRAY_BUFFER, g_point_count * 2 * sizeof (float), &g_vt[0], GL_STATIC_DRAW);
	
    glEnableVertexAttribArray (loc1);
	glBindBuffer (GL_ARRAY_BUFFER, vp_vbos.back());
	glVertexAttribPointer (loc1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
	glEnableVertexAttribArray (loc2);
	glBindBuffer (GL_ARRAY_BUFFER, vn_vbos.back());
	glVertexAttribPointer (loc2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
    glEnableVertexAttribArray (loc3);
    glBindBuffer (GL_ARRAY_BUFFER, vt_vbos.back());
    glVertexAttribPointer (loc3, 2, GL_FLOAT, GL_FALSE, 0, NULL);

}
#pragma endregion VBO_FUNCTIONS



#pragma region USER_FUNCTIONS
void keypress(unsigned char key, int x, int y)
{
    //if(t.elapsedTime() <= GAME_LENGTH_SECONDS) {
    
    update_cam_positions();
    float scale = 0.003f;
    switch(key){
    case 'j': cam.ProcessKeyboard(Camera_Movement(LEFT), scale );
        break;
    case 'k': cam.ProcessKeyboard(Camera_Movement(BACKWARD), scale );
        break;
    case 'l': cam.ProcessKeyboard(Camera_Movement(RIGHT),scale );
        break;
    case 'i': cam.ProcessKeyboard(Camera_Movement(FORWARD), scale );
        break;
    case 'a': cam.ProcessKeyboard(Camera_Movement(SOUTH_EAST), scale );
    default: break;
    }

}

void mouse(int x, int y)
{

    //if(t.elapsedTime() <= GAME_LENGTH_SECONDS)
    //{
    
        if (firstMouse)
        {
            lastX = x;
            lastY = y;
            firstMouse = false;
        }
    
        GLfloat xoffset = x - lastX;
        GLfloat yoffset = lastY - y; // Reversed since y-coordinates go from bottom to left
        lastX = x;
        lastY = y;
    
        cam.ProcessMouseMovement(xoffset, yoffset);
        //std::cout << "Camera Position: " << cam.getPosition().x << " " << cam.getPosition().y << " " << cam.getPosition().z << " " << endl;
    //}
    //else cout << "GAME OVER! score: " << score << endl;


}

int count_non_valid_meshes()
{
    int count;
    for(int i=0;i<valid_meshes.size();i++){
        if(valid_meshes[i]==false) count++;
    }
    cout << "" << endl;
    SoundEngine->play2D("/Users/tadhgriordan/Documents/Course/4th Year/Graphics/Assignments/OpenGL/Lab 5/include/sounds/collect.wav", false);
    return count;
}

bool detect_through_ring(vector<vec3> ring_points_from_centroid, glm::vec3 positionGLM)
{

    bool detected=false;
    vec3 position = convert_glm_vec3(positionGLM);
    for(int i=0;i<ring_points_from_centroid.size() && !detected;i++)
    {
        vec3 currPoint = ring_points_from_centroid[i];
        if((fabs(currPoint.v[X]-position.v[X])<=.1) && (fabs(currPoint.v[Y]-position.v[Y])<=.5) && (fabs(currPoint.v[Z]-position.v[Z])<=.5))
        {
            detected = true;
            return detected;
        }
    }
    return false;
}

void get_centroid(vector<float> points)
{
    vec3 result;
    float totalx=0;
    float totaly=0;
    float totalz=0;
    
    for(int i=0;i<points.size();i+=3){
        totalx += points[i];
        totaly += points[i+1];
        totalz += points[i+2];
    }
    
    
    cout << "totals: " << totalx << " " << totaly << " " << totalz << endl;
    cout << "points size: " << points.size() << endl;
    cout << "points size: /3  " << points.size()/3 << endl;
    
    float avgx = totalx/(points.size()/3);
    float avgy = totaly/(points.size()/3);
    float avgz = totalz/(points.size()/3);
    
    cout << "centroid point (unrounded): " << avgx << " " << avgy << " " << avgz << endl;
    
    avgx = roundfs(avgx);
    avgy = roundfs(avgy);
    avgz = roundfs(avgz);
    
    cout << "centroid point (rounded): " << avgx << " " << avgy << " " << avgz << endl;
    
    ring_centroids.push_back(vec3(avgx,avgy,avgz));
    
}

void get_points_from_centroid(vector<float> points, int ring, vec3 centroid)
{
    //this function takes the centroid of a ring and all its points
    //it calculates all the line points from the centroid and stores them globally
    //this will be used when detecting movement through a ring.
    //the formula for this is P1 + t(P2-P1) where t is the interpolation factor (the step between points).
    //this will be set to .1.
    

    float t = .1;
    //cout << "points size: " << points.size() << endl;
    //cout << "ring: " << ring << endl;
    vector<vec3> ring_points_from_centroid;
    for(int i=0;i<points.size();i+=3)
    {
        vec3 b = vec3(points[i],points[i+1],points[i+2]);
        //cout << "ok" << endl;
        if(fabs(b.v[X]-centroid.v[X])<=.1 || fabs(b.v[Y]-centroid.v[Y])<=.1 || fabs(b.v[Z]-centroid.v[Z])<=.1)
        {
            //cout << "z within bounds" << endl;
            vec3 negation = b-centroid;
            negation.v[X] = t * negation.v[X];
            negation.v[Y] = t * negation.v[Y];
            negation.v[Z] = t * negation.v[Z];
            vec3 result = centroid + negation;
            ring_points_from_centroid.push_back(result);
        }
    }
    
    for(int i=0;i<ring_points_from_centroid.size();i++){
        vec3 curr = ring_points_from_centroid[i];
        //cout << "centre plane points: " << curr.v[X] << " " << curr.v[Y] << " " << curr.v[Z] << endl;
    }
    
    ring_points_from_centroids.push_back(ring_points_from_centroid);
    
}
#pragma endregion USER_FUNCTIONS


#pragma startregion CONSTANT_FUNCTIONS
void updateScene()
{
    
    // Placeholder code, if you want to work with framerate
    // Wait until at least 16ms passed since start of last frame (Effectively caps framerate at ~60fps)
    
    cout << t.elapsedTime() << endl;
    

    // rotate the model slowly around the y axis
    //rotate_y+=10.2f;
    // Draw the next frame
    glutPostRedisplay();
}

void display()
{
    
    // tell GL to only draw onto a pixel if the shape is closer to the viewer
    glDepthRange(0,1);
    glEnable (GL_DEPTH_TEST); // enable depth-testing  
    glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as "closer"
    
    glClearColor (0.5f, 0.5f, 0.5f, 1.0f);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glUseProgram (shaderProgramID);
     
    //Declare your uniform variables that will be used in your shader
    int matrix_location = glGetUniformLocation (shaderProgramID, "model");
    int view_mat_location = glGetUniformLocation (shaderProgramID, "view");
    int proj_mat_location = glGetUniformLocation (shaderProgramID, "proj");
      
    glm::mat4 view = glm::mat4(1.0);
    view = glm::translate(view, glm::vec3(0.0, 0.0, -5.0f));
    view = glm::lookAt(cam.Position, cam.Position + cam.Front, cam.Up);
    
    mat4 persp_proj = perspective(45.0, (float)width/(float)height, 0.1, 100.0);
    
    // update uniforms & draw
    glUniformMatrix4fv (view_mat_location, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv (proj_mat_location, 1, GL_FALSE, persp_proj.m);
    
    for(int mesh=0;mesh<NUM_MESHES;mesh++)
    {
        if(valid_meshes[mesh]){
        glBindVertexArray(mesh_vaos[mesh]);
        models[mesh] = identity_mat4();
        //models[mesh] = translate(models[mesh], vec3(2.0f,2.0f,2.0f));
        if(mesh >= 44)
        {
            models[mesh] = translate(models[mesh], ring_translations[mesh-44]);
            if(first_iteration) //if first display call, we translate rings and set up ring-pass detection.
            {
                translate_positions(mesh,models[mesh]);
                get_centroid(mesh_vps[mesh]);
                get_points_from_centroid(mesh_vps[mesh], NUM_MESHES, ring_centroids[mesh-44]);
            }
        }
        glBindTexture(GL_TEXTURE_2D, textures[mesh]);
        glUniformMatrix4fv (matrix_location, 1, GL_FALSE, models[mesh].m);
        glDrawArrays (GL_TRIANGLES, 0, mesh_point_counts[mesh]);
        }
    }
    d_count++;
    first_iteration = false;
    glBindVertexArray(0);
    
    for(int ring=(int)RING_0;ring<NUM_MESHES;ring++)
    {
        find_collision(mesh_vps[ring], cam.getPosition());
        if(detect_through_ring(ring_points_from_centroids[ring-(int)RING_0], cam.getPosition()))
        {
            valid_meshes[ring] = false;
            score = count_non_valid_meshes();
            cout << "SCORE: " << score << endl;

        }
    }
    
    glutSwapBuffers();
}

void init()
{
    // Set up the shaders
    unsigned int vao = 0;
    glGenVertexArrays (1, &vao);
    glBindVertexArray (vao); //A VAO must be bound for program to run.
    
    GLuint shaderProgramID = CompileShaders();
    
    load_object_names();
    load_texture_names();
    load_ring_translations();
    
    for(int i=0;i<object_names.size();i++)
    {
        const aiScene* scene = load_object(object_names[i]);
        for(int j=0;j<scene->mNumMeshes;j++)
        {
            clear_globals();
            mesh_vaos[NUM_MESHES] = NUM_MESHES;
            glGenVertexArrays (1, &mesh_vaos[NUM_MESHES]);
            glBindVertexArray(mesh_vaos[NUM_MESHES]);

            generateObjectBufferMesh(scene,j,mesh_vaos[NUM_MESHES]);
            mesh_point_counts.push_back(g_point_count);
            mesh_vps.push_back(g_vp);
            NUM_MESHES++;
        }
        aiReleaseImport(scene);
    }

    cout << "num meshes: " << NUM_MESHES << endl;
    for(int i=0;i<NUM_MESHES;i++){
        valid_meshes.push_back(true);
    }
    SoundEngine->play2D("/Users/tadhgriordan/Documents/Course/4th Year/Graphics/Assignments/OpenGL/Lab 5/include/sounds/background.wav", true);
    t.start();
}
#pragma endregion CONSTANT_FUNCTIONS

int main(int argc, char** argv){

	// Set up the window
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_3_2_CORE_PROFILE|GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutCreateWindow("");
    
	// Tell glut where the display function is
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutKeyboardFunc(keypress);
    
    glutPassiveMotionFunc(mouse);
	 // A call to glewInit() must be done after glut is initialized!
    glewExperimental = GL_TRUE;
    GLenum res = glewInit();
	// Check for any errors
    if (res != GLEW_OK) {
      fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
      return 1;
    }
	// Set up your objects and shaders
	init();
	// Begin infinite event loop
	glutMainLoop();
    return 0;
}

